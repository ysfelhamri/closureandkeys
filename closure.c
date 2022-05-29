#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 50
typedef struct
{
    char **p_g;
    char **p_d;
    int count_g;
    int count_d;
} DF;
typedef struct
{
    char **p;
    int t;
} Ens;
struct list
{
    Ens *data;
    struct list *next;
};
void aff_DF(const DF a);
void alloc_DF(DF *const a, const int n1, const int n2, const int si);
void saisG_DF(DF *const a, const int pos, const char *const g);
void saisD_DF(DF *const a, const int pos, const char *const d);
void aff_Ens(const Ens r);
void alloc_Ens(Ens *const r, const int n, const int si);
void sais_Ens(Ens *const r, const int pos, const char *const v);
void realloc_Ens(Ens *const r, const int n, const int si);
int comp(const DF a, const Ens b);
void cp_Ens(Ens *const a, const Ens b);
int pres_DFG(const DF a, const char *const s, const int pos);
int pres_DFD(const DF a, const char *const s, const int pos);
int pre_Ens(const Ens r, const char *const s, const int pos);
void desalloc_Ens(Ens *const a);
void desalloc_DF(DF *const a);
int comp_Ens(const Ens a, const Ens b);
Ens **comb(const Ens e);
int comp_ens2(const Ens a, const Ens b);
int comp_cles(struct list *head, const Ens e);
struct list *aj_cle(struct list *head, const Ens e);
int saisieG(DF *const a, int count1, const int n1, const Ens rel, const int si);
void saisieD(DF *const a, const int count1, int count2, const int n1, const Ens rel, const int si);
int main()
{
    DF **les_df;
    Ens *R, *rel, *sto;
    int i, j, k, n1, n2, n3, count1, count2, test, choix, ch;
    char c[N];
    Ens **combi;
    struct list *head = NULL;

        n1 = 0;
        n3 = 0;
        do
        {
            printf("------------------------------------\n");
            printf("|  1.Calculate the closure      |\n");
            printf("|  2.Calculate candidate keys   |\n");
            printf("------------------------------------\n");
            printf("Type your choice :");
            scanf("%d", &choix);

        } while (choix != 1 && choix != 2);

        rel = (Ens *)malloc(sizeof(Ens));
        if (rel == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        alloc_Ens(rel, 1, N);
        printf("-Type 0 to exit the input-\n");
        while (1)
        {
            do
            {
                printf("Enter the attribute -%d- of the relation :", n1 + 1);
                scanf("%s", c);
                if (!strcmp(c, "0"))
                {
                    if (n1 < 2)
                        break;
                    realloc_Ens(rel, -1, N);
                    break;
                }
            } while (pre_Ens(*rel, c, n1));
            if (!strcmp(c, "0") && (n1 < 2))
                continue;
            if (!strcmp(c, "0"))
                break;
            sais_Ens(rel, n1, c);
            realloc_Ens(rel, 1, N);
            n1++;
        }
        printf("------------------------------------\n");
        aff_Ens(*rel);
        printf("\n------------------------------------\n");
        combi = comb(*rel);
        do
        {
            printf("Enter the number of FD's:");
            scanf("%d", &n2);
        } while (n2 < 1);

        les_df = (DF **)malloc(n2 * sizeof(DF *));
        if (les_df == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        for (i = 0; i < n2; i++)
        {
            les_df[i] = (DF *)malloc(sizeof(DF));
            if (les_df[i] == NULL)
            {
                printf("Memory allocation error");
                exit(33);
            }
        }

        for (i = 0; i < n2; i++)
        {
            count1 = 0;
            count2 = 0;
            printf("---------------*%d* FD---------------\n", i + 1);
            alloc_DF(les_df[i], 1, 1, N);

            printf("-------------|____| -> -------------\n");
            printf("-Type 0 to exit the input-\n");
            count1 = saisieG(les_df[i], count1, n1, *rel, N);

            printf("------------- -> |____|-------------\n");
            printf("-Type 0 to exit the input-\n");
            saisieD(les_df[i], count1, count2, n1, *rel, N);
        }

        sto = (Ens *)malloc(sizeof(Ens));
        if (sto == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        switch (choix)
        {
        case 1:

            printf("------------------------------------\n");
            aff_Ens(*rel);
            printf("\n");
            for (i = 0; i < n2; i++)
            {
                aff_DF(*les_df[i]);
                printf("\n");
            }
            printf("------------------------------------\n");


            R = (Ens *)malloc(sizeof(Ens));
            if (R == NULL)
            {
                printf("Memory allocation error");
                exit(33);
            }
            alloc_Ens(R, 1, N);
            printf("-Type 0 to exit the input-\n");
            while (1)
            {
                do
                {
                    printf("Enter the attribute -%d- of the set:", n3 + 1);
                    scanf("%s", c);
                    if (!strcmp(c, "0"))
                    {
                        if (n3 <= 0)
                            break;
                        realloc_Ens(R, -1, N);
                        break;
                    }
                } while (pre_Ens(*R, c, n3));
                if (!strcmp(c, "0") && (n3 <= 0))
                    continue;
                if (!strcmp(c, "0"))
                    break;
                sais_Ens(R, n3, c);
                realloc_Ens(R, 1, N);
                n3++;
            }


            printf("------------------------------------\n");
            aff_Ens(*rel);
            printf("\n");
            for (i = 0; i < n2; i++)
            {
                aff_DF(*les_df[i]);
                printf("\n");
            }
            cp_Ens(sto, *R);
            printf("\n------------------------------------\n");

            do
            {
                test = sto->t;
                for (i = 0; i < n2; i++)
                    if (comp(*les_df[i], *sto))
                        for (j = 0; j < les_df[i]->count_d; j++)
                            if (!pre_Ens(*sto, les_df[i]->p_d[j], sto->t))
                            {
                                realloc_Ens(sto, 1, N);
                                sais_Ens(sto, sto->t - 1, les_df[i]->p_d[j]);
                            }
            } while ((test != sto->t));
            printf("The closure is: ");
            aff_Ens(*R);
            printf("+ = ");
            aff_Ens(*sto);
            printf("\n------------------------------------\n");
            if (comp_Ens(*rel, *sto))
            {
                aff_Ens(*R);
                printf(" is a key");
            }
            else
            {
                aff_Ens(*R);
                printf(" is not a key");
            }
            desalloc_Ens(R);
            free(R);
            break;

        case 2:

            printf("------------------------------------\n");
            aff_Ens(*rel);
            printf("\n");
            for (i = 0; i < n2; i++)
            {
                aff_DF(*les_df[i]);
                printf("\n");
            }
            printf("------------------------------------\n");
            printf("The keys are: ");
            for (k = 0; k < pow(2, n1) - 1; k++)
            {
                cp_Ens(sto, *combi[k]);
                if (comp_cles(head, *sto))
                {
                    do
                    {
                        test = sto->t;
                        for (i = 0; i < n2; i++)
                            if (comp(*les_df[i], *sto))
                                for (j = 0; j < les_df[i]->count_d; j++)
                                    if (!pre_Ens(*sto, les_df[i]->p_d[j], sto->t))
                                    {
                                        realloc_Ens(sto, 1, N);
                                        sais_Ens(sto, sto->t - 1, les_df[i]->p_d[j]);
                                    }
                    } while ((test != sto->t));
                    if (comp_Ens(*rel, *sto))
                    {
                        aff_Ens(*combi[k]);
                        printf(" ");
                        head = aj_cle(head, *combi[k]);
                    }
                }
                desalloc_Ens(combi[k]);
                free(combi[k]);
            }
            break;
        }
        for (i = 0; i < n2; i++)
        {
            desalloc_DF(les_df[i]);
            free(les_df[i]);
        }
        free(les_df);
        desalloc_Ens(rel);
        free(rel);
        free(combi);
        desalloc_Ens(sto);
        free(sto);
        free(head);
}
void alloc_DF(DF *const a, const int n1, const int n2, const int si)
{
    if (a == NULL)
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    a->p_g = (char **)malloc(n1 * sizeof(char *));
    if (a->p_g == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    for (i = 0; i < n1; i++)
    {
        a->p_g[i] = (char *)malloc(si * sizeof(char));
        if (a->p_g[i] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
    }
    a->p_d = (char **)malloc(n2 * sizeof(char *));
    if (a->p_d == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    for (i = 0; i < n2; i++)
    {
        a->p_d[i] = (char *)malloc(si * sizeof(char));
        if (a->p_d[i] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
    }
    a->count_g = n1;
    a->count_d = n2;
}
void saisG_DF(DF *const a, const int pos, const char *const g)
{
    if ((a->p_g == NULL) || (a == NULL) || (g == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    strcpy(a->p_g[pos], g);
}
void saisD_DF(DF *const a, const int pos, const char *const d)
{
    if ((a->p_d == NULL) || (a == NULL) || (d == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    strcpy(a->p_d[pos], d);
}
void aff_DF(const DF a)
{
    if ((a.p_d == NULL) || (a.p_g == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < a.count_g - 1; i++)
        printf("%s,", a.p_g[i]);
    printf("%s", a.p_g[a.count_g - 1]);
    printf(" -> ");
    for (i = 0; i < a.count_d - 1; i++)
        printf("%s,", a.p_d[i]);
    printf("%s", a.p_d[a.count_d - 1]);
}
int comp(const DF a, const Ens b)
{
    if ((b.p == NULL) || (a.p_d == NULL) || (a.p_g == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i, j, c;
    for (i = 0; i < a.count_g; i++)
    {
        c = 0;
        for (j = 0; j < b.t; j++)
        {
            if (strcmp(b.p[j], a.p_g[i]))
                c++;
            else
                break;
        }
        if (c == b.t)
            return 0;
    }
    return 1;
}
void alloc_Ens(Ens *const r, const int n, const int si)
{
    if (r == NULL)
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    r->p = (char **)malloc(n * sizeof(char *));
    if (r->p == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    for (i = 0; i < n; i++)
    {
        r->p[i] = (char *)malloc(si * sizeof(char));
        if (r->p[i] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
    }
    r->t = n;
}
void sais_Ens(Ens *const r, const int pos, const char *const v)
{
    if ((r->p == NULL) || (r == NULL) || (v == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    strcpy(r->p[pos], v);
}
void realloc_Ens(Ens *const r, const int n, const int si)
{
    if ((r->p == NULL) || (r == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    r->p = (char **)realloc(r->p, ((r->t) + n) * sizeof(char *));
    if (r->p == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    for (i = r->t; i < ((r->t) + n); i++)
    {
        r->p[i] = (char *)malloc(si * sizeof(char));
        if (r->p[i] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
    }
    r->t += n;
}
void aff_Ens(const Ens r)
{
    if (r.p == NULL)
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    printf("{");
    for (i = 0; i < r.t - 1; i++)
        printf("%s,", r.p[i]);
    printf("%s", r.p[r.t - 1]);
    printf("}");
}
void cp_Ens(Ens *const a, const Ens b)
{
    if ((a == NULL) || (b.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    alloc_Ens(a, b.t, N);
    for (i = 0; i < b.t; i++)
        sais_Ens(a, i, b.p[i]);
}
int pres_DFG(const DF a, const char *const s, const int pos)
{
    if ((s == NULL) || (a.p_d == NULL) || (a.p_g == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < pos; i++)
        if (!strcmp(a.p_g[i], s))
            return 1;
    return 0;
}
int pres_DFD(const DF a, const char *const s, const int pos)
{
    if ((s == NULL) || (a.p_d == NULL) || (a.p_g == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    if (pres_DFG(a, s, a.count_g))
        return 1;
    for (i = 0; i < pos; i++)
        if (!strcmp(a.p_d[i], s))
            return 1;
    return 0;
}
int pre_Ens(const Ens r, const char *const s, const int pos)
{
    if ((s == NULL) || (r.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < pos; i++)
        if (!strcmp(r.p[i], s))
            return 1;
    return 0;
}
void desalloc_Ens(Ens *const a)
{
    if ((a == NULL) || (a->p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < a->t; i++)
        free(a->p[i]);
    free(a->p);
}
void desalloc_DF(DF *const a)
{
    if ((a == NULL) || (a->p_g == NULL) || (a->p_d == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < a->count_d; i++)
        free(a->p_d[i]);
    free(a->p_d);
    for (i = 0; i < a->count_g; i++)
        free(a->p_g[i]);
    free(a->p_g);
}
int comp_Ens(const Ens a, const Ens b)
{
    if ((a.p == NULL) || (b.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    if (a.t != b.t)
        return 0;
    int i, j, c;
    for (i = 0; i < a.t; i++)
    {
        c = 0;
        for (j = 0; j < b.t; j++)
        {
            if (strcmp(b.p[j], a.p[i]))
                c++;
            else
                break;
        }
        if (c == b.t)
            return 0;
    }
    return 1;
}
Ens **comb(const Ens e)
{
    if ((e.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    Ens **res;
    int k, s = pow(2, e.t) - 1;
    res = (Ens **)malloc(s * sizeof(Ens *));
    if (res == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    for (k = 0; k < s; k++)
    {
        res[k] = (Ens *)malloc(sizeof(Ens));
        if (res[k] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }

        res[k]->p = NULL;
        res[k]->t = 0;
    }
    int i, j, bin, q, r, end, c2;
    int pt[e.t];
    for (j = 1; j <= s; j++)
    {
        for (i = 0; i < e.t; i++)
            pt[i] = 0;
        end = e.t - 1;
        bin = j;
        c2 = 0;
        do
        {
            q = bin / 2;
            r = bin % 2;
            bin = q;
            pt[end--] = r;
        } while (q != 0);
        for (i = 0; i < e.t; i++)
            if (pt[i] == 1)
            {
                if (res[j - 1]->p == NULL)
                    alloc_Ens(res[j - 1], 1, N);
                else
                    realloc_Ens(res[j - 1], 1, N);
                sais_Ens(res[j - 1], c2, e.p[i]);
                c2++;
            }
    }
    return res;
}

int comp_ens2(const Ens a, const Ens b)
{
    if ((a.p == NULL) || (b.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    int i;
    for (i = 0; i < a.t; i++)
        if (pre_Ens(b, a.p[i], b.t))
            return 1;
    return 0;
}
struct list *aj_cle(struct list *head, const Ens e)
{
    if ((e.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    struct list *new = (struct list *)malloc(sizeof(struct list));
    if (new == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    new->data = (Ens *)malloc(sizeof(Ens));
    if (new->data == NULL)
    {
        printf("Memory allocation error");
        exit(33);
    }
    alloc_Ens(new->data, e.t, N);
    cp_Ens(new->data, e);
    new->next = head;
    head = new;
    return head;
}
int comp_cles(struct list *head, const Ens e)
{
    if ((e.p == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    struct list *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->data->t != e.t)
            if (comp_ens2(e, *tmp->data))
                return 0;
        tmp = tmp->next;
    }
    return 1;
}
int saisieG(DF *const a, int count1, const int n1, const Ens rel, const int si)
{
    if ((rel.p == NULL) || (a->p_g == NULL) || (a == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }

    char c[si];
    while (1)
    {
        // printf("         count1 === %d         ",count1);
        do
        {
            if (count1 + 1 >= n1)
            {
                a->p_g = (char **)realloc(a->p_g, (a->count_g - 1) * sizeof(char *));
                a->count_g--;
                return count1;
            }
            printf("Enter the attribute -%d- of the left part:", count1 + 1);
            scanf("%s", c);
            if (!strcmp(c, "0"))
            {
                if (count1 <= 0)
                    continue;
                a->p_g = (char **)realloc(a->p_g, (a->count_g - 1) * sizeof(char *));
                a->count_g--;
                return count1;
            }
        } while (pres_DFG(*a, c, count1) || !pre_Ens(rel, c, rel.t));
        saisG_DF(a, count1, c);
        a->p_g = (char **)realloc(a->p_g, (a->count_g + 1) * sizeof(char *));
        if (a->p_g == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        a->p_g[a->count_g] = (char *)malloc(si * sizeof(char));
        if (a->p_g[a->count_g] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        a->count_g++;
        count1++;
    }
}
void saisieD(DF *const a, const int count1, int count2, const int n1, const Ens rel, const int si)
{
    if ((rel.p == NULL) || (a->p_d == NULL) || (a == NULL))
    {
        printf("NULL pointer error");
        exit(33);
    }
    char c[si];
    while (1)
    {
        // printf("         count1 === %d         ",count1);
        do
        {
            if (count2 + 1 > (n1 - count1))
            {
                a->p_d = (char **)realloc(a->p_d, (a->count_d - 1) * sizeof(char *));
                a->count_d--;
                return;
            }
            printf("Enter the attribute -%d- of the right part:", count2 + 1);
            scanf("%s", c);
            if (!strcmp(c, "0"))
            {
                if (count2 <= 0)
                    continue;
                a->p_d = (char **)realloc(a->p_d, (a->count_d - 1) * sizeof(char *));
                a->count_d--;
                return;
            }
        } while (pres_DFD(*a, c, count2) || !pre_Ens(rel, c, rel.t));
        saisD_DF(a, count2, c);
        a->p_d = (char **)realloc(a->p_d, (a->count_d + 1) * sizeof(char *));
        if (a->p_d == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        a->p_d[a->count_d] = (char *)malloc(si * sizeof(char));
        if (a->p_d[a->count_d] == NULL)
        {
            printf("Memory allocation error");
            exit(33);
        }
        a->count_d++;
        count2++;
    }
}
