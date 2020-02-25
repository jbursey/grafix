using System;
using System.Collections.Generic;
using System.Text;

namespace Grafix.TerrainCreator
{
    struct Vec2d
    {
        public double x;
        public double y;
    }

    class Perlin
    {
        private List<List<Vec2d>> _grid = new List<List<Vec2d>>();

        private int _maxX = 10;
        private int _maxY = 10;
        private int _rows = 10;
        private int _cols = 10;

        public Perlin(int maxX, int maxY, int rows, int cols)
        {
            _maxX = maxX;
            _maxY = maxY;

            //grid definition with random gradient vectors unit length
            Random random = new Random();            
            _rows = rows;
            _cols = cols;
            for (int x = 0; x < _rows; x++)
            {
                List<Vec2d> row = new List<Vec2d>(); ;
                for (int z = 0; z < _cols; z++)
                {
                    Vec2d v;
                    v.x = (random.NextDouble() * 2.0) - 1;
                    v.y = (random.NextDouble() * 2.0) - 1;
                    Vec2d norm = Normalize(v);
                    row.Add(norm);
                }

                _grid.Add(row);
            }

            int asdfjlasf = 0;
        }

        public double Noise(int inx, int iny)
        {            



            //dot product given a cordinate x,y
            //int X = 35;
            //int Y = 12;            

            /*

                

            */

            //double perlinX = (inx * (rows - 1)) / (MAX_X * 1.0);
            //double perlinY = (iny * (cols - 1)) / (MAX_Y * 1.0);
            double perlinX = (inx / (_maxX * 1.0)) * (_rows - 1);
            double perlinY = (iny / (_maxY * 1.0)) * (_cols - 1);

            List<double> dotProducts = GetDotProductsWithCorners(perlinX, perlinY);

            //interpolation
            double val = Interpolate(perlinX, perlinY, dotProducts);

            //Console.WriteLine($"X: {inx}, Y: {iny}, PerlinX: {perlinX}, PerlinY: {perlinY}, Noise: {val}");

            return val;
        }

        private Vec2d Normalize(Vec2d vec)
        {
            double magnitude = Math.Sqrt((vec.x * vec.x) + (vec.y * vec.y));

            Vec2d norm = new Vec2d();
            if (magnitude > 0)
            {
                norm.x = vec.x / magnitude;
                norm.y = vec.y / magnitude;
            }
            else
            {
                norm.x = 0;
                norm.y = 0;
            }

            return norm;
        }

        private double Interpolate(double perlinX, double perlinY, List<double> dots)
        {
            int x = (int)Math.Floor(perlinX);
            int y = (int)Math.Floor(perlinY);

            double d0 = dots[0];
            double d1 = dots[1];
            double d2 = dots[2];
            double d3 = dots[3];

            double dx = perlinX - x;
            double dy = perlinY - y;

            //dx = weigh(dx);
            //dy = weigh(dy);

            double a = Lerp(d0, d1, dx);
            double b = Lerp(d2, d3, dx);
            double c = Lerp(a, b, dy);
            return c;
        }

        //private double weigh(double x)
        //{
        //    return 3 * (x * x) - 2 * (x * x * x);
        //}

        private double Lerp(double a, double b, double factor)
        {
            double lerp = 0;

            /*

             Lets assume a = 5 and b = 13 and factor = 0.25
             then b - a = 8

             lerp = ((b-a) * factor) + a

             */

            lerp = ((b - a) * factor) + a;

            return lerp;

            //return (1.0f - factor) * a + factor * b;

            //double value = factor * factor * factor * (factor * (factor * 6 - 15) + 10);
            //return a + value * (b - a);
        }

        private Vec2d GetDirectionVector(double x1, double y1, double x2, double y2)
        {
            Vec2d v;
            v.x = x2 - x1;
            v.y = y2 - y1;

            return v;
        }

        private List<double> GetDotProductsWithCorners(double perlinX, double perlinY)
        {
            int x = (int)Math.Floor(perlinX);
            int y = (int)Math.Floor(perlinY);

            Vec2d v1 = _grid[x][y];
            Vec2d v2 = _grid[x + 1][y];
            Vec2d v3 = _grid[x][y + 1];
            Vec2d v4 = _grid[x + 1][y + 1];
  
            Vec2d dirV1 = GetDirectionVector(x, y, perlinX, perlinY);           
            Vec2d dirV2 = GetDirectionVector(x + 1, y, perlinX, perlinY);
            Vec2d dirV3 = GetDirectionVector(x, y+1, perlinX, perlinY);
            Vec2d dirV4 = GetDirectionVector(x + 1, y + 1, perlinX, perlinY);           

            dirV1 = Normalize(dirV1);
            dirV2 = Normalize(dirV2);
            dirV3 = Normalize(dirV3);
            dirV4 = Normalize(dirV4);            



            double dotV1 = (dirV1.x * v1.x) + (dirV1.y * v1.y);
            double dotV2 = (dirV2.x * v2.x) + (dirV2.y * v2.y);
            double dotV3 = (dirV3.x * v3.x) + (dirV3.y * v3.y);
            double dotV4 = (dirV4.x * v4.x) + (dirV4.y * v4.y);

           

            List<double> dotProducts = new List<double>();
            dotProducts.Add(dotV1);
            dotProducts.Add(dotV2);
            dotProducts.Add(dotV3);
            dotProducts.Add(dotV4);

            return dotProducts;
        }

    }
}
