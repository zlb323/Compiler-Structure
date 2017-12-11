using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication3
{
    class top
    {
        private static top instance = null;
        private static readonly object padlock = new object();
        private Dictionary<string, node> dict = new Dictionary<string, node>();
        private List<group> groups = new List<group>();
        private List<id> ids = new List<id>();

        public top()
        {
        }

        public static top get()
        {
            lock (padlock)
            {
                if(instance == null)
                {
                    instance = new top();
                }
            }
            return instance;
        }

        public void addKeyword(string word, node n)
        {
            n.print();
            try
            {
                dict.Add(word, n);
            }
            catch
            {
                Console.WriteLine("KeyWord already used");
            }
        }

        public node getNode(string key, string type)
        { 
            node n;
            if (dict.TryGetValue(key, out n))
            {
                return n;
            }
            else if (type == "group")
            {
                group g = new group(type, key);
                top.get().addGroup(g);
                return g;
            }
            else if (type == "id")
            {
                id i = new id(type, key);
                top.get().addId(i);
                return i;
            }
            else if (type == "variable") return new variable(key, type, "");
            else if (type == "command") return new command(type, key, new List<string>());
            else if (type == "word") return new node(type, key);
            else return new node("node", key);
        }
        public void addGroup(group g)
        {
            groups.Add(g);
        }

        public void addId(id i)
        {
            ids.Add(i);
        }

        public string print()
        {
            string t = "";
            foreach(group g in groups)
            {
                t = t + g.print();
            }
            return t;
        }
        public string printids()
        {
            foreach( group g in groups)
            {
                g.evalOffsets();
                g.setValues();
            }
            string t = "";
            foreach (id i in ids)
            {
                i.evalOffsets();
                t = t + i.print();
            }
            return t;
        }
    }

    class node
    {
        private string type;
        private string word;

        public string getT()
        {
            return type;
        }

        public string get()
        {
            return word;
        }

        public node(string _type, string _word)
        {
            type = _type;
            word = _word;
            top p = top.get();
            p.addKeyword(_word, this);
        }
        public virtual string print()
        {
            return word;
        }

    }

    class id : node
    {
        List<node> commands = new List<node>();
        List<offset> offsets = new List<offset>();
        public id(string _type, string _word)
            : base(_type, _word)
        {
        }

        public void addOffset(offset o)
        {
            offsets.Add(o);
        }
        public void evalOffsets()
        {
            foreach(offset o in offsets)
            {
                foreach(command c in commands)
                {
                    if (o.getTarget() == c.getAttr())
                    {
                        c.offset(o.getVals(), o.getIsPositive());
                    }

                }
            }
        }

        public void addNode(node n)
        {
            commands.Add(n);
        }
        public override string print()
        {
            string g = "";
            g += base.print() + "\n{\n";
                foreach (node com in commands)
                {
                    g = g + com.print() + "\n";
                }
                g = g + "}\n";
            return g;
        }

    }
    
    class group : node
    {
        List<node> commands = new List<node>();
        List<id> names = new List<id>();
        List<offset> offsets = new List<offset>();
        public group(string _type, string _word)
            : base(_type, _word)
        {
        }

        public void addNode(node n)
        {
            commands.Add(n);
        }

        public void addNames(id n)
        {
            names.Add(n);
        }
        public void setValues()
        {
            foreach(id i in names)
            {
                foreach(node c in commands)
                {
                    command a = new command(((command)c).getT(), ((command)c).getAttr(), ((command)c).getVals());

                    i.addNode(a);
                }
            }
        }
        public void addOffset(offset o)
        {
            offsets.Add(o);
        }
        public void evalOffsets()
        {
            foreach (offset o in offsets)
            {
                foreach (id i in names)
                {
                    i.addOffset(o);
                }
            }
        }
        public string print()
        {
            setValues();
            string g = "";
            foreach (node nam in names)
            {
                if(nam != null) g = g + nam.get() + "\n{\n";
                foreach (node com in commands)
                {
                    g = g + com.print() + "\n";
                }
                g = g + "}\n";
            }
            return g;
        }
    }
    
    class command : node
    {
        List<string> values = new List<string>();
        string attribute;
        public command(string _type, string _text, List<string> _values)
            :base(_type, _text)
        {
            attribute = _text;
            values = _values;
        }
        public List<string> getVals()
        {
            return values;
        }
        public string getAttr()
        {
            return attribute;
        }
        public void addValues(List<string> vals)
        {
            values.AddRange(vals);
        }
        public void offset(string off, bool positive)
        {
            if (positive)
            {
                for (int i = 0; i < values.Count(); i++)
                {
                    if (values[i][0] == '$')
                    {
                        values[i] = getCalcValue((HextoInt(((variable)top.get().getNode(values[i], "variable")).print()) + HextoInt(off)));
                    }
                    else if (values[i][0] == '0' && values[i][1] == 'x') values[i] = getCalcValue(HextoInt(values[i]) + HextoInt(off));
                }
            }
            else
            {
                for (int i = 0; i < values.Count(); i++)
                {
                    if (values[i][0] == '$')
                    {
                        values[i] = getCalcValue((HextoInt(((variable)top.get().getNode(values[i], "variable")).print()) - HextoInt(off)));
                    }
                    else if (values[i][0] == '0' && values[i][1] == 'x') values[i] = getCalcValue(HextoInt(values[i]) - HextoInt(off));
                }
            }
        }
        public int HextoInt(string hex)
        {
            int i = Convert.ToInt32(hex, 16);
            return i;
        }
        public string printHex(string hex)
        {
            string temp = "#";
            for(int i = hex.Length; i < 6; i++)
            {
                temp += "0";
            }
            return hex.Insert(0, temp);
        }
        public string getCalcValue(int a)
        {
            return a.ToString("X");
        }
        public override string print()
        { 
            string temp;
            temp = attribute + ":";
            node n = null;
            variable v = null;
            foreach (string a in values)
            {
                string t = a;
                if ((n = top.get().getNode(a, "")) != null)
                {
                    if (n.getT() == "variable")
                    {
                        v = (variable)n;
                        t = v.print();
                    }
                }
                int aa;
                if ((t[0] == '0' && t[1] == 'x') || Int32.TryParse(t, out  aa)) temp = temp + " " + printHex(getCalcValue(HextoInt(t)));
                else temp = temp + " " + t;
            }
            temp = temp + ";";
            return temp;
        }
    }
    class variable : node
    {
        string value;
        public variable(string _word, string _type, string _value)
            :base(_type, _word)
        {
            value = _value;
        }
        public void setValue(string val)
        {
            value = val;
        }
        public string print()
        {
            return value;
        }

    }

    class offset : node
    {
        string target;
        string off;
        bool isPositive;
        public offset(string _target, string o, bool _p)
            :base("offset", _target)
        {
            target = _target;
            off = o;
            isPositive = _p;
        }
        public string getTarget()
        {
            return target;
        }
        public string getVals()
        {
            return off;
        }
        public bool getIsPositive()
        {
            return isPositive;
        }
    }
}
