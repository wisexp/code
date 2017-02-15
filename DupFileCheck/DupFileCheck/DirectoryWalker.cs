using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DupFileCheck
{
    public delegate void Visit(string file);
    public class DirectoryWalker
    {
        
        public void Walk(string root, Visit visit)
        {

            try
            {
                var files = Directory.GetFiles(root);

                foreach (var file in files)
                {
                    visit(file);
                }
            }catch (Exception ex)
            { }

            try
            {
                var dirs = Directory.GetDirectories(root);
                foreach (var dir in dirs)
                {
                    Walk(dir, visit);
                }
            }catch(Exception ex)
            {

            }
        }

        
    }
}
