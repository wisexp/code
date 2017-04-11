using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
namespace DownloadTickData
{
    public class Data
    {
        public float High;
        public float Low;
        public int Vol;

        public static Data ParseOne(string line)
        {
            Data data = null;
            var seg = line.Split(new char[] { ',' });
            if (seg.Count() == 3)
            {
                data = new Data();
                data.High = float.Parse(seg[0]);
                data.Low = float.Parse(seg[1]);
                data.Vol = int.Parse(seg[2]);
            }

            return data;
        }

        public static List<Data> ParseMultiple(string str)
        {

            //EXCHANGE%3DNASDAQ
            //MARKET_OPEN_MINUTE=570
            //MARKET_CLOSE_MINUTE=960
            //INTERVAL=60
            //COLUMNS=HIGH,LOW,VOLUME
            //DATA=
            //TIMEZONE_OFFSET=-300
            //825.615,825.5,29080
            //826.927,825.615,6658
            //828.54,827.24,2830
            System.IO.StringReader sr = new System.IO.StringReader(str);
            for (int i = 0; i < 7; i++) sr.ReadLine();
            List<Data> data = new List<Data>();
            while (true)
            {
                var line = sr.ReadLine();
                if (line == null) break;

                data.Add(Data.ParseOne(line));

            }
            return data;
            
        }
    }
    public class GOOGLE
    {
        static string template = "https://www.google.com/finance/getprices?i=60&p=1d&f=h,l,v&df=cpct&q={0}";
        static public List<Data> Download(string ticker)
        {
            string url = string.Format(template, ticker);
            WebClient wc = new WebClient();
            var data = wc.DownloadData(url);
            return Data.ParseMultiple(System.Text.Encoding.UTF8.GetString(data));
        }

    }
}
