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

        

        void Implement(int inx, int iny)
        {
            Random random = new Random((int)DateTime.Now.Ticks);

            //grid definition with random gradient vectors unit length
            int rows = 10;
            int cols = 10;
            for (int x = 0; x < rows; x++)
            {
                List<Vec2d> row = new List<Vec2d>(); ;
                for (int z = 0; z < cols; z++)
                {
                    Vec2d v;
                    v.x = random.NextDouble();
                    v.y = random.NextDouble();
                    row.Add(v);
                }

                _grid.Add(row);
            }

            //dot product given a cordinate x,y
            //int X = 35;
            //int Y = 12;
            int MAX_X = 100;
            int MAX_Y = 100;

            /*

            x =>  35     X
                 ---- = ----
                 100     10

            x => X = (x * rows) / maxX

            */

            double perlinX = (inx * (rows - 1)) / (MAX_X * 1.0);
            double perlinY = (iny * (cols - 1)) / (MAX_Y * 1.0);

            List<double> dotProducts = GetDotProductsWithCorners(perlinX, perlinY);

            //interpolation
            double val = Lerp(perlinX, perlinY, dotProducts);
        }

        private List<double> GetDotProductsWithCorners(double perlinX, double perlinY)
        {
            int x = (int)Math.Floor(perlinX);
            int y = (int)Math.Floor(perlinX);

            Vec2d v1 = _grid[x][y];
            Vec2d v2 = _grid[x + 1][y];
            Vec2d v3 = _grid[x][y + 1];
            Vec2d v4 = _grid[x + 1][y + 1];

            List<Vec2d> vecs = new List<Vec2d>();
            vecs.Add(v1);
            vecs.Add(v2);
            vecs.Add(v3);
            vecs.Add(v4);

            Vec2d dirV1;
            dirV1.x = v1.x - perlinX;
            dirV1.y = v1.y - perlinY;

            Vec2d dirV2;
            dirV2.x = v2.x - perlinX;
            dirV2.y = v2.y - perlinY;

            Vec2d dirV3;
            dirV3.x = v3.x - perlinX;
            dirV3.y = v3.y - perlinY;

            Vec2d dirV4;
            dirV4.x = v4.x - perlinX;
            dirV4.y = v4.y - perlinY;

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



        double Lerp(double perlinX, double perlinY, List<double> dots)
        {
            int x = (int)Math.Floor(perlinX);
            int y = (int)Math.Floor(perlinX);

            double d0 = dots[0];
            double d1 = dots[1];
            double d2 = dots[2];
            double d3 = dots[3];

            // a = lerp(dots[0], dots[1], perlinX - x)
            // b = lerp(dots[2], dots[3], perlinX - x)
            // c = lerp(a, b, perlinY - y)
            // return c;


            return 0;
        }

    }
}
