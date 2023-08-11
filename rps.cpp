#include <bits/stdc++.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
using namespace std;
typedef vector<tuple<char, int, int, int>> FSA;
typedef vector<tuple<int, int>> vertices;

int search_for_imp(int x, int y, vertices imp)
{
    for (int i = 0; i < imp.size(); ++i)
    {
        int a = get<0>(imp[i]);
        int b = get<1>(imp[i]);
        if (a == x && b == y)
        {
            break;
            return 1;
        }
    }
    return 0;
}

int CheckW_L(char a, char b)
{
    if (a == 'P' && b == 'S')
    {
        return 1;
    }
    else if (a == 'R' && b == 'P')
    {
        return 1;
    }
    else if (a == 'S' && b == 'R')
    {
        return 1;
    }
    else if (a == b)
    {
        return 0;
    }
    return 0;
}

int main()
{
    srand(time(0));
    int n;
    cin >> n;
    if (n > 30)
    {
        printf("Input has more than 30 states\n");
        exit(0);
    }
    int x = n;
    FSA input_FSA;
    while (x > 0)
    {
        x--;
        char a;
        int r, p, s;
        scanf("%s %d %d %d", &a, &r, &p, &s);
        input_FSA.push_back(make_tuple(a, r, p, s));
    }
    int flag1 = 0, flag2 = 0, flag3 = 0;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int pp = 1, ps = 1, sr = 1, ss = 1, rr = 1, rp = 1, rs = 1, pr = 1, sp = 1;
    while (x < n)
    {
        char a;
        int r, p, s;
        a = get<0>(input_FSA[x]);
        r = get<1>(input_FSA[x]);
        p = get<2>(input_FSA[x]);
        s = get<3>(input_FSA[x]);
        if (a == 'P' && flag1 == 0)
        {
            pp = p;
            ps = s;
            pr = r;
        }
        else if (a == 'R' && flag2 == 0)
        {
            rs = s;
            rp = p;
            rr = r;
        }
        else if (a == 'S' && flag3 == 0)
        {
            sp = p;
            sr = r;
            ss = s;
        }
        ++x;
    }
    x = 0;

    FSA output_FSA;
    vertices imp;

    while (x < n)
    {
        int index1, index2;
        char a, a_out;
        int temp, r_out, p_out, s_out;
        a = get<0>(input_FSA[x]);
        if (a == 'R')
        {
            a_out = 'P';
            index2 = 2;
            index1 = 1;
            output_FSA.push_back(make_tuple(a_out, 1, 1, 1));
            get<1>(output_FSA[x]) = get<2>(input_FSA[x]);
            get<2>(output_FSA[x]) = pp;
            get<3>(output_FSA[x]) = sp;
            imp.push_back(make_tuple(0, x));
        }
        else if (a == 'P')
        {
            a_out = 'S';
            index2 = 3;
            index1 = 2;
            output_FSA.push_back(make_tuple(a_out, 1, 1, 1));
            get<1>(output_FSA[x]) = rs;
            get<2>(output_FSA[x]) = get<3>(input_FSA[x]);
            get<3>(output_FSA[x]) = ss;
            imp.push_back(make_tuple(1, x));
        }
        else if (a == 'S')
        {
            a_out = 'R';
            index2 = 1;
            index1 = 3;
            output_FSA.push_back(make_tuple(a_out, 1, 1, 1));
            get<1>(output_FSA[x]) = rr;
            get<2>(output_FSA[x]) = pr;
            get<3>(output_FSA[x]) = get<1>(input_FSA[x]);
            imp.push_back(make_tuple(2, x));
        }
        ++x;
    }
    printf("%d\n", n);
    x = 0;
    int count = 0;
    int loss_count = 1;

    for (int j = 0; j < 10; ++j)
    {
        for (int i = 1; i < n; ++i)
        {
            {
                int input_traversor = i;
                int output_traversor = 0;
                int input_prev;
                int output_prev;
                // Code for simulation
                for (int s = 0; s < 1400; ++s)
                {
                    char a_o;
                    int r_o, p_o, s_o;
                    a_o = get<0>(output_FSA[output_traversor]);
                    r_o = get<1>(output_FSA[output_traversor]);
                    p_o = get<2>(output_FSA[output_traversor]);
                    s_o = get<3>(output_FSA[output_traversor]);
                    char a_i;
                    int r_i, p_i, s_i;
                    a_i = get<0>(input_FSA[input_traversor]);
                    r_i = get<1>(input_FSA[input_traversor]);
                    p_i = get<2>(input_FSA[input_traversor]);
                    s_i = get<3>(input_FSA[input_traversor]);
                    input_prev = input_traversor;
                    output_prev = output_traversor;
                    if (a_i == 'R')
                    {
                        output_traversor = r_o - 1;
                    }
                    else if (a_i == 'P')
                    {
                        output_traversor = p_o - 1;
                    }
                    else if (a_i == 'S')
                    {
                        output_traversor = s_o - 1;
                    }
                    if (a_o == 'R')
                    {
                        input_traversor = r_i - 1;
                    }
                    else if (a_o == 'P')
                    {
                        input_traversor = p_i - 1;
                    }
                    else if (a_o == 'S')
                    {
                        input_traversor = s_i - 1;
                    }

                    if (input_traversor == output_traversor)
                    {
                        count = 0;
                        break;
                    }
                    int result = CheckW_L(a_i, a_o);
                    if (result == 1)
                    {
                    }
                    else
                    {
                        ++count;
                        if (count > loss_count)
                        {
                            tuple<char, int, int, int> swap_tuple;
                            loss_count = count;
                            count = 0;
                            char a, b;
                            int x1, y1, z1;
                            a = get<0>(input_FSA[input_prev]);
                            b = get<0>(output_FSA[output_prev]);
                            x1 = get<1>(output_FSA[output_prev]);
                            y1 = get<2>(output_FSA[output_prev]);
                            z1 = get<3>(output_FSA[output_prev]);
                            if (a == 'R' && search_for_imp(0, output_traversor, imp) == 0)
                            {
                                x1 = input_traversor + 1;
                                imp.push_back((make_tuple(0, output_traversor)));
                            }
                            else if (a == 'P' && search_for_imp(1, output_traversor, imp) == 0)
                            {
                                y1 = input_traversor + 1;
                                imp.push_back((make_tuple(1, output_traversor)));
                            }
                            else if (a == 'S' && search_for_imp(1, output_traversor, imp) == 0)
                            {
                                z1 = input_traversor + 1;
                                imp.push_back((make_tuple(2, output_traversor)));
                            }
                            swap_tuple = make_tuple(b, x1, y1, z1);
                            output_FSA[output_prev].swap(swap_tuple);
                        }
                    }
                }
                count = 0;
            }
        }
    }

    while (x < n)
    {
        char a;
        int r, p, s;
        a = get<0>(output_FSA[x]);
        r = get<1>(output_FSA[x]);
        p = get<2>(output_FSA[x]);
        s = get<3>(output_FSA[x]);
        printf("%c %d %d %d\n", a, r, p, s);
        ++x;
    }
    x = 0;

    return 0;
}