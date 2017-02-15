using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DupFileCheck
{
    public class FileInformation
    {
        public FileInformation(string file)
        {
            name = file;
            hash = 0;
            size = 0;
            try
            {
                FileInfo fi = new FileInfo(file);
            size = fi.Length;
           
            creationTime = fi.CreationTime;
           
                using (BinaryReader sr = new BinaryReader(File.Open(file, FileMode.Open)))
                {
                    int index = 0;
                    int count = 1024;
                    int div = 2;
                    int maxSize = (int)size;
                    hash = 5381;

                    while (index < maxSize)
                    {
                        byte[] buffer = sr.ReadBytes(count);
                        ApplyHash(buffer);
                        index += maxSize / div + count;
                        sr.BaseStream.Seek(index, SeekOrigin.Begin);
                        div *= 2;
                    }

                }
            }
            catch (Exception ex)
            {

            }
        }

        public void Dump()
        {
            Console.WriteLine("size {0}, hash {1}, name {2}", size, hash, name);
        }

        void ApplyHash(byte[] str)
        {
                     

            foreach(var c in str)
                hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

           
        }

        public string Name { get { return name; } }
        public long Size { get { return size; } }
        public int Hash { get { return (int)hash; } }
        public DateTime CreationTime { get { return creationTime; } }
        string name;
        long size;
        long hash;
        DateTime creationTime;
    }
}
