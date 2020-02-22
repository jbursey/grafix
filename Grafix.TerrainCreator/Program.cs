using System;
using System.Drawing;

namespace Grafix.TerrainCreator
{
    class Program
    {
        static void Main(string[] args)
        {           
            CreateBitmap();
            Console.WriteLine(".......done");
            Console.ReadLine();
        }

        static void CreateBitmap()
        {
            int width = 1000;
            int height = 1000;

            //Perlin perlin = new Perlin(width, height, 6, 6);            
            Perlin3 perlin = new Perlin3(10, 10, width, height);
            Bitmap bitmap = new Bitmap(width, height);
            bitmap.SetPixel(0, 0, Color.FromArgb(255, 128, 50, 10));
            unsafe
            {
                var bitmapData = bitmap.LockBits(new Rectangle(0, 0, width, height), System.Drawing.Imaging.ImageLockMode.ReadWrite, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                IntPtr nptr = bitmapData.Scan0;
                int* ptr = (int*)nptr.ToPointer();
                for (int i = 0; i < width; i++)
                {
                    for (int j = 0; j < height; j++)
                    {                        
                        double noise = perlin.Noise(i, j);
                        byte val = (byte)ScaleNoiseToBitmap(noise);
                        //Console.WriteLine($"Noise: {noise}");
                        if(val == 255)
                        {
                            //Console.WriteLine($"X: {i}, Y: {j}");
                        }
                        //Console.WriteLine($"Noise: {noise} --> Color: {val}");

                        //int color = *ptr;
                        //byte a = (byte)(color >> 24);
                        //byte r = (byte)(color >> 16);
                        //byte g = (byte)(color >> 8);
                        //byte b = (byte)(color >> 0);
                       
                        int color = 0;
                        if (i == -1 && j == 0)
                        {
                            color |= (255) << 24;
                            color |= (255) << 16;
                            color |= (0) << 8;
                            color |= (0) << 0;                            
                        }
                        else
                        {
                            color |= (255) << 24;
                            color |= (val) << 16;
                            color |= (val) << 8;
                            color |= (val) << 0;
                        }

                        *ptr = color;
                        ++ptr;
                    }
                }
                bitmap.UnlockBits(bitmapData);
            }

            //bitmap.SetPixel(0, 0, Color.FromArgb(255, 255, 0, 0));

            //string csv = "";
            //for(int i = 0; i < width; i++)
            //{
            //    for(int j = 0; j < height; j++)
            //    {
            //        double noise = perlin.Noise(i, j);
            //        int rgba = ScaleNoiseToBitmap(noise);
            //        bitmap.SetPixel(i, j, Color.FromArgb(255, rgba, rgba, rgba));
            //        //Console.WriteLine($"Noise: {noise}");
            //        csv += noise + "\n";
            //        int stop = 0;
            //    }

            //    if( i == 4)
            //    {
            //        int ssafd = 0;
            //    }
            //}

            bitmap.Save(@"F:\Jeff\perlin\perlin.png", System.Drawing.Imaging.ImageFormat.Png);
            bitmap.Save(@"F:\Jeff\perlin\perlin.bmp", System.Drawing.Imaging.ImageFormat.Bmp);

            int asdfsadf = 0;
        }

        static int ScaleNoiseToBitmap(double noise)
        {
            noise = noise + 1.0; //make it 0-2

            int val = (int)(noise * 128);
            if(val < 0)
            {
                val = 0;
            }
            if(val > 255)
            {
                val = 255;
            }

            return val;
        }
    }
}
