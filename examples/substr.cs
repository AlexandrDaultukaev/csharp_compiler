System.String s1 = "Hello World!";
System.String s2 = "orl";
bool b = s1.Contains(s2);
if (b)
{
    int index = s1.IndexOf(s2);
    if (index >= 0)
        System.Console.WriteLine(index);
}
