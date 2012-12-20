#include "../memory.h"
#include "../string.h"
#include "elf.h"

unsigned int elf_validate(struct elf_header *header)
{

    char id[] = {ELF_IDENTITY_MAGIC0, ELF_IDENTITY_MAGIC1, ELF_IDENTITY_MAGIC2, ELF_IDENTITY_MAGIC3};

    return memory_match(header->identify, id, 4);

}

unsigned int elf_find_section(struct elf_header *header, struct elf_section_header *sectionHeader, unsigned int type)
{

    unsigned int i;

    for (i = 0; i < header->shcount; i++)
    {

        if (sectionHeader[i].type == type)
            return i;

    }

    return 0;

}

unsigned int elf_find_symbol(struct elf_header *header, struct elf_section_header *sectionHeader, unsigned int symbolHeaderIndex, struct elf_symbol *symbolTable, char *stringTable, char *symbol)
{

    unsigned int length = string_length(symbol);
    unsigned int i;

    for (i = 0; i < sectionHeader[symbolHeaderIndex].size / sectionHeader[symbolHeaderIndex].esize; i++)
    {

        if (memory_match(symbol, stringTable + symbolTable[i].name, length + 1))
            return (header->type == ELF_TYPE_RELOCATABLE) ? sectionHeader[symbolTable[i].shindex].address + sectionHeader[symbolTable[i].shindex].offset + symbolTable[i].value : symbolTable[i].value;

    }

    return 0;

}

void elf_relocate_symbol(unsigned int address, unsigned int type, unsigned int addend)
{

    unsigned int *entry = (unsigned int *)(address);

    switch (type)
    {

        case ELF_RELOC_TYPE_32:

            *entry += addend;

            break;

        case ELF_RELOC_TYPE_PC32:

            *entry += addend - address;

            break;

    }

}

void elf_relocate_section(struct elf_section_header *sectionHeader, unsigned int relocateHeaderIndex, unsigned int relocateDataIndex, struct elf_relocate *relocateTable, struct elf_symbol *symbolTable, unsigned int address)
{

    unsigned int i;

    for (i = 0; i < sectionHeader[relocateHeaderIndex].size / sectionHeader[relocateHeaderIndex].esize; i++)
    {

        unsigned char type = relocateTable[i].info & 0x0F;
        unsigned char index = relocateTable[i].info >> 8;
        unsigned int offset = sectionHeader[relocateDataIndex].offset + relocateTable[i].offset;
        unsigned int addend = sectionHeader[symbolTable[index].shindex].offset + symbolTable[index].value;

        if (symbolTable[index].shindex)
            elf_relocate_symbol(address + offset, type, address + addend);
        else
            elf_relocate_symbol(address + offset, type, 0);

    }

}

