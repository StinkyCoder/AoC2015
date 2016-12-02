using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Fourth
{
    class Program
    {

        public static string CalculateMD5Hash(string input){
            // step 1, calculate MD5 hash from input
            MD5 md5 = System.Security.Cryptography.MD5.Create();
            byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
            byte[] hash = md5.ComputeHash(inputBytes);
            // step 2, convert byte array to hex string
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < hash.Length; i++){

                sb.Append(hash[i].ToString("X2"));
            }
            return sb.ToString();
        }

        static void Main(string[] args)
        {
                int i = 0;
            //while (true)
            //{
            //    string temp = CalculateMD5Hash("abcdef" + i);
            //    if (temp.StartsWith("00000")) { 
            //        break;
            //    } else
            //    {
            //        i++;
            //    }                
            //}
            //Console.WriteLine(CalculateMD5Hash("abcdef" + i) );
            //Console.WriteLine ( i);
            // i = 0;
            //while (true)
            //{
            //    string temp = CalculateMD5Hash("pqrstuv" + i);
            //    if (temp.StartsWith("00000"))
            //    {
            //        break;
            //    }
            //    else
            //    {
            //        i++;
            //    }
            //}
            //Console.WriteLine(CalculateMD5Hash("pqrstuv" + i));
            //Console.WriteLine(i);
            //i = 0;
            while (true)
            {
                string temp = CalculateMD5Hash("iwrupvqb" + i);
                if (temp.StartsWith("000000"))
                {
                    break;
                }
                else
                {
                    i++;
                }
            }
            Console.WriteLine(CalculateMD5Hash("iwrupvqb" + i));
            Console.WriteLine(i);
            Console.ReadLine();
        }
    }
}
