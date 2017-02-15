using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DupFileCheck
{
    class Program
    {
        static void Main(string[] args)
        {

            string sqlCon = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=D:\code\DupFileCheck\DupFileCheck\Database1.mdf;Integrated Security=True;Connect Timeout=30";
            using (SqlConnection Con = new SqlConnection(sqlCon))
            {
                Con.Open();
                int id = 0;
                DirectoryWalker dw = new DirectoryWalker();
                dw.Walk("E:\\", (string f) =>
                {

                    try
                    {
                        var fi = new FileInformation(f);
                        SqlCommand cmd = new SqlCommand(string.Format("insert into FileInfo (Id, Path, Size, Hash, CreationTime) Values ({3}, N'{0}', {1}, {2}, '{4}')",
                            fi.Name.Replace("'", "''"), fi.Size, fi.Hash, id++, fi.CreationTime.ToString("yyyy-MM-ddThh:mm:ss")), Con);
                        cmd.ExecuteNonQuery();
                    }catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                });
            }

            int k = 0;
        }
    }
}
