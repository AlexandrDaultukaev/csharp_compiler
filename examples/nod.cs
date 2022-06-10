int a = 15;
int b = 12;

for (int i = a; i > 0; i--)
{
    int res = a % i;
    if (res == 0)
    {
        res = b % i;
        if (res == 0)
        {
            break;
        }
    }
}
