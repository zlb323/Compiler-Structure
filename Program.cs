using Antlr4.Runtime;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using Antlr4.Runtime.Standard;


namespace ConsoleApplication3
{
    class Program
    {
        static void Main(string[] args)
        {
            var input = System.IO.File.ReadAllText(@"C:\Users\zach1\Desktop\School\classes\C#\ConsoleApplication3\intput.txt");
            try
            {
                AntlrInputStream inputStream = new AntlrInputStream(input);
                cssLexer cl = new cssLexer(inputStream);
                CommonTokenStream cms = new CommonTokenStream(cl);
                cssParser cp = new cssParser(cms);

                cssParser.ExpressionsContext expressionscontext = cp.expressions();
                CSSVisitor visitor = new CSSVisitor();

                visitor.Visit(expressionscontext);

                File.WriteAllText(@"C:\Users\zach1\Desktop\test.css", top.get().printids());
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex);
            }
            Console.ReadKey();
        }
    }
}
