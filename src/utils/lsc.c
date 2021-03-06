#include <abi.h>
#include <fudge.h>

void main(void)
{

    struct record record;
    char num[FUDGE_NSIZE];

    file_open(FILE_PO);
    file_open(FILE_PW);
    file_writeall(FILE_PO, num, ascii_wzerovalue(num, FUDGE_NSIZE, 0, 16, 8, 0));
    file_writeall(FILE_PO, " ", 1);
    file_writeall(FILE_PO, num, ascii_wzerovalue(num, FUDGE_NSIZE, 0, 16, 8, 0));
    file_writeall(FILE_PO, " ", 1);
    file_writeall(FILE_PO, "..\n", 3);

    while (file_readall(FILE_PW, &record, sizeof (struct record)))
    {

        file_writeall(FILE_PO, num, ascii_wzerovalue(num, FUDGE_NSIZE, record.id, 16, 8, 0));
        file_writeall(FILE_PO, " ", 1);
        file_writeall(FILE_PO, num, ascii_wzerovalue(num, FUDGE_NSIZE, record.size, 16, 8, 0));
        file_writeall(FILE_PO, " ", 1);
        file_writeall(FILE_PO, record.name, record.length);
        file_writeall(FILE_PO, "\n", 1);
        file_step(FILE_PW);

    }

    file_close(FILE_PW);
    file_close(FILE_PO);

}

