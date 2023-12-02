#include "lab.h"

#define add_neighbour(neighbour)                                                                                   \
    if ((lab.mas[neighbour].elem == ' ' &&  lab.mas[neighbour].value == 1) || lab.mas[neighbour].elem == 'o')      \
    {                                                                                                              \
        lab.mas[neighbour].value = 0;                                                                              \
        lst[lst_size].elem = neighbour;                                                                            \
        lst[i].next = lst_size;                                                                                    \
        lst[lst_size].prev = i;                                                                                    \
        lst_size++;                                                                                                \
        if (lab.mas[neighbour].elem == 'o')                                                                        \
            return (RET_LIST){lst, lst_size};                                                                      \
    }


RET_LIST lab_solve(LAB lab)
{
    int start = lab.in_y * lab.x + lab.in_x;

    lab.mas[start].value = 0;

    LIST* lst = (LIST*)calloc(lab.x * lab.y, sizeof(LIST));

    assert(lst != NULL);

    size_t lst_size = 1;

    lst[0].elem = start;
    int new_start = 0;

    while (true)
    {
        int save_lst_size = lst_size;

        for (int i = new_start; i < save_lst_size; i++)
        {
            int cur_x = lst[i].elem % (lab.x);
            int cur_y = lst[i].elem / (lab.x);

            //priority of neighbours
            add_neighbour(cur_y * lab.x + cur_x + 1); //right
            add_neighbour((cur_y + 1) * lab.x + cur_x); //down
            add_neighbour((cur_y - 1) * lab.x + cur_x); //up
            add_neighbour(cur_y * lab.x + cur_x - 1);   //left
        }

        if (!lst[save_lst_size].elem)
        {
            printf(RED "DEAD END. No solutions\n" END_OF_COLOUR);
            return {};
        }

        new_start = save_lst_size;
    }
}

void lab_dump(LAB lab)
{
    printf(GREEN "--------------------------\n" END_OF_COLOUR);

    size_t current_line = 0;

    for (int i = 0; i < lab.x * lab.y; i++)
    {
        if ((lab.mas[i]).value == 1)
            printf(RED "%c" END_OF_COLOUR, lab.mas[i].elem);
        else
            printf(GREEN "%c" END_OF_COLOUR, lab.mas[i].elem);

        if ((i + 1)%lab.x == 0)
            printf("\n");
    }
    printf(GREEN "--------------------------\n" END_OF_COLOUR);
}

LAB lab_read(FILE* source)
{
    fseek(source, 0, SEEK_END);
    int file_size = ftell(source);
    fseek(source, 0, SEEK_SET);

    char* buf = (char*)calloc(file_size, sizeof(char));

    assert(buf != NULL);

    fread(buf, sizeof(char), file_size, source);

    char current_symbol = *buf;
    size_t index = 0;

    LAB lab = {};
    lab.mas = (VERTEX*)calloc(file_size, sizeof(VERTEX));
    int i = 0;

    int current_x = 0;
    int current_y = 0;

    while (current_symbol != '\0')
    {
        switch (current_symbol)
        {
            case '#':
                current_x++;
                lab.mas[i].elem = '#';
                lab.mas[i].value = 1;
                break;
            case '\n':
                i--;
                if (*(buf+1) != '\0' )
                    current_x = 0;
                current_y++;
                break;
            case 'o':
                lab.mas[i].elem = 'o';
                lab.mas[i].value = 1;
                lab.out_x = current_x;
                lab.out_y = current_y;
                current_x++;
                break;
            case 'i':
                lab.mas[i].elem = 'i';
                lab.mas[i].value = 1;
                lab.in_x = current_x;
                lab.in_y = current_y;
                current_x++;
                break;
            case ' ':
                current_x++;
                lab.mas[i].elem = ' ';
                lab.mas[i].value = 1;
                break;
            default:
            {
                printf(RED "ERROR: Unknown symbol in lab\n" END_OF_COLOUR);
                return {};
            }
        }

        current_symbol = *(++buf);
        i++;
    }

    lab.mas[i].elem = '\0';
    lab.x = current_x;
    lab.y = current_y;

    free(buf);

    return lab;
}


