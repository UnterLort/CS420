#include <stdio.h>
/* Created by Kyle Stewart on 2/5/2024. */

int main()
{
    int train = 0, on, off, tot_off = 0;
    scanf("%d", &train);

    for (int s = 0; s < 5; s++)
    {
        scanf("%d", &off);

        while (off > on)
        {
            scanf("%d", &off);
        }

        train -= off;

        if (s < 4)
        {
            scanf("%d", &on);

            while (on < 0 || on > 25)
            {
                scanf("%d", &on);
            }
            train += on;
        }
        tot_off += off;
    }
    return 0;
}