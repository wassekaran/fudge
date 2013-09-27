#include <fudge/kernel.h>
#include "vfs.h"
#include "binary.h"

static unsigned int match(struct vfs_session *session, unsigned int id)
{

    struct elf_header header;

    if (session->protocol->read(session->backend, id, 0, ELF_HEADER_SIZE, &header) < ELF_HEADER_SIZE)
        return 0;

    return elf_validate(&header);

}

static unsigned int find_symbol(struct vfs_session *session, unsigned int id, unsigned int count, const char *symbol)
{

    struct elf_header header;
    struct elf_section_header sectionheader[32];
    unsigned int i;

    session->protocol->read(session->backend, id, 0, ELF_HEADER_SIZE, &header);

    if (header.shcount > 32)
        return 0;

    session->protocol->read(session->backend, id, header.shoffset, header.shsize * header.shcount, sectionheader);

    for (i = 0; i < header.shcount; i++)
    {

        struct elf_symbol symbols[512];
        char strings[4096];
        unsigned int address;
        struct elf_section_header *symbolheader;
        struct elf_section_header *stringheader;

        if (sectionheader[i].type != ELF_SECTION_TYPE_SYMTAB)
            continue;

        symbolheader = &sectionheader[i];
        stringheader = &sectionheader[symbolheader->link];

        if (symbolheader->size > sizeof (struct elf_symbol) * 512)
            return 0;

        if (stringheader->size > 4096)
            return 0;

        session->protocol->read(session->backend, id, symbolheader->offset, symbolheader->size, symbols);
        session->protocol->read(session->backend, id, stringheader->offset, stringheader->size, strings);

        address = elf_find_symbol(&header, sectionheader, symbolheader, symbols, strings, count, symbol);

        if (address)
            return address;

    }

    return 0;

}

static unsigned int copy_program(struct vfs_session *session, unsigned int id)
{

    struct elf_header header;
    struct elf_program_header programheader[8];
    unsigned int i;

    session->protocol->read(session->backend, id, 0, ELF_HEADER_SIZE, &header);

    if (header.phcount > 8)
        return 0;

    session->protocol->read(session->backend, id, header.phoffset, header.phsize * header.phcount, programheader);

    for (i = 0; i < header.phcount; i++)
        session->protocol->read(session->backend, id, programheader[i].offset, programheader[i].fsize, (void *)programheader[i].vaddress);

    return header.entry;

}

static unsigned int relocate(struct vfs_session *session, unsigned int id, unsigned int address)
{

    struct elf_header header;
    struct elf_section_header sectionheader[32];
    unsigned int i;

    session->protocol->read(session->backend, id, 0, ELF_HEADER_SIZE, &header);

    if (header.shcount > 32)
        return 0;

    session->protocol->read(session->backend, id, header.shoffset, header.shsize * header.shcount, sectionheader);

    for (i = 0; i < header.shcount; i++)
    {

        struct elf_relocation relocations[512];
        struct elf_symbol symbols[512];
        struct elf_section_header *relocationheader;
        struct elf_section_header *dataheader;
        struct elf_section_header *symbolheader;

        sectionheader[i].address += address;

        if (sectionheader[i].type != ELF_SECTION_TYPE_REL)
            continue;

        relocationheader = &sectionheader[i];
        dataheader = &sectionheader[relocationheader->info];
        symbolheader = &sectionheader[relocationheader->link];

        if (relocationheader->size > sizeof (struct elf_relocation) * 512)
            return 0;

        if (symbolheader->size > sizeof (struct elf_symbol) * 512)
            return 0;

        session->protocol->read(session->backend, id, relocationheader->offset, relocationheader->size, relocations);
        session->protocol->read(session->backend, id, symbolheader->offset, symbolheader->size, symbols);
        elf_relocate_section(sectionheader, relocationheader, dataheader, relocations, symbols, address);

    }

    session->protocol->write(session->backend, id, header.shoffset, header.shsize * header.shcount, sectionheader);

    return 1;

}

void binary_init_elf(struct binary_protocol *protocol)
{

    memory_clear(protocol, sizeof (struct binary_protocol));
    binary_init_protocol(protocol, match, find_symbol, copy_program, relocate);

}

