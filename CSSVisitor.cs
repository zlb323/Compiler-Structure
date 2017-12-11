using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
namespace ConsoleApplication3
{
    public class CSSVisitor : cssBaseVisitor<object>
    {
        public override object VisitGroupassign([NotNull] cssParser.GroupassignContext context)
        {
            group knew = (group)top.get().getNode(context.WORD().GetText(), "group");// new group("Group", context.WORD().GetText());
            int j = 0;
            while(context.ID(j) != null)
            {
                knew.addNames((id)top.get().getNode(context.ID(j).GetText(), "id"));
                j++;
            }
            int i = 0;
            while (context.assignment(i) != null)
            {
                if (context.assignment(i).GetText().Contains("Offset")) knew.addOffset((offset)Visit(context.assignment(i)));
                else knew.addNode((command)Visit(context.assignment(i)));
                i++;
            }
            return knew;
        }

        public override object VisitIdassign([NotNull] cssParser.IdassignContext context)
        {
            Console.Write(context.ID().GetText());
            id i = (id)top.get().getNode(context.ID().GetText(), "id");
            int num = 0;
            while (context.assignment(num) != null)
            {
                if (context.assignment(num).GetText().Contains("Offset")) i.addOffset((offset)Visit(context.assignment(num)));
                else i.addNode((command)Visit(context.assignment(num)));
                num++;
            }
            return i;
        }

        public override object VisitOffset([NotNull] cssParser.OffsetContext context)
        {
            bool isPos;
            if (context.SIGN().GetText() == "-") isPos = false;
            else isPos = true;
            return new offset(context.WORD().GetText(), context.HEX().GetText(), isPos);
        }
        
        public override object VisitCommand([NotNull] cssParser.CommandContext context)
        {
            List<string> temp = new List<string>();
            int i = 1;
            while (context.WORD(i) != null)
            {
                temp.Add(context.WORD(i).GetText());
                i++;
            }
            i = 0;
            while (context.Variable(i) != null)
            {
                temp.Add(context.Variable(i).GetText());
                i++;
            }
            i = 0;
            while (context.HEX(i) != null)
            {
                temp.Add(context.HEX(i).GetText());
                i++;
            }
            command knew = new command("command", context.WORD(0).GetText(), temp);// (command) top.get().getNode(context.WORD(0).GetText(), "command");// new command("command", context.WORD(0).GetText(), temp);
            knew.get();
            return knew;
        }
        public override object VisitVarassign([NotNull] cssParser.VarassignContext context)
        {
            variable n = (variable) top.get().getNode(context.Variable().GetText(), "variable");// null;
            if (context.WORD() != null) n.setValue(context.WORD().GetText());
            else if (context.HEX() != null) n.setValue(context.HEX().GetText());
            return n;
        }
    }
}
