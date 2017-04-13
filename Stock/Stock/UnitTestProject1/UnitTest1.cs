using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using DownloadTickData;
namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            var str = DownloadTickData.GOOGLE.Download("ABAX");
            int k = 0;

        }
    }
}
