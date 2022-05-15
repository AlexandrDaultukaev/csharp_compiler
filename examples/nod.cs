int a = 15;
int b = 12;

for (int i = a; i > 0; i--)
{
    if (a % i == 0)
    {
        if (b % i == 0)
        {
            System.Console.WriteLine(i);
            break;
        }
    }
}
