using System;
using System.IO;


class SubStr
{
    static void Main(string[] args)
    {
        String s1 = Console.ReadLine();
        String s2 = Console.ReadLine();
        bool b = s1.Contains(s2);
        Console.WriteLine("'{0}' is in the string '{1}': {2}",
                        s2, s1, b);
        if (b)
        {
            int index = s1.IndexOf(s2);
            if (index >= 0)
                Console.WriteLine("'{0} begins at character position {1}",
                            s2, index + 1);
        }
    }
}
