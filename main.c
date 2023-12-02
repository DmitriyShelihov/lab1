#include "lab.h"

int main()
{
    FILE* source = fopen("lab.txt", "r");

    assert(source != NULL);

    LAB lab = lab_read(source);

    RET_LIST ret_lst = lab_solve(lab);

    LIST* lst = ret_lst.lst;

    int current_index = lst[ret_lst.ans_index - 1].prev;

    int way = 1;

    while (current_index != 0)
    {
        lab.mas[lst[current_index].elem].elem = '.';
        current_index = lst[current_index].prev;
        way++;
    }

    lab_dump(lab);

    printf(BLUE "The shortest way is %d\n" END_OF_COLOUR, way);

    free(lst);
    free(lab.mas);
    return 0;
}
