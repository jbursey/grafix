using System;
using System.Collections.Generic;
using System.Text;

namespace Grafix.TerrainCreator
{
    public class Perlin3
    {
        private class Vec2d
        {
            public double X;
            public double Y;

            public Vec2d(double x, double y)
            {
                this.X = x;
                this.Y = y;
            }

            public void Normalize()
            {
                double mag = Math.Sqrt((this.X * this.X) + (this.Y * this.Y));
                if (mag > 0)
                {
                    this.X = this.X / mag;
                    this.Y = this.Y / mag;
                }
            }

            public double Dot(Vec2d vec)
            {
                return (this.X * vec.X) + (this.Y * vec.Y);
            }


        }

        private int _width;
        private int _height;
        private int _maxWidth;
        private int _maxHeight;

        private List<Vec2d> _gradients;

        public Perlin3(int width, int height, int maxWidth, int maxHeight)
        {
            this._width = width;
            this._height = height;
            this._maxWidth = maxWidth;
            this._maxHeight = maxHeight;

            this._gradients = new List<Vec2d>();

            InitGradients();
        }

        public double Noise(double x, double y)
        {
            double originalX = x;
            double originalY = y;

            //--translate x "grid" space
            x = (x / (_maxWidth * 1.0)) * _width;
            y = (y / (_maxHeight * 1.0)) * _height;

            //--find nodes
            int x0 = (int)x; //top left
            int y0 = (int)y; //top left
            int x1 = x0 + 1; //bottom right
            int y1 = y0 + 1; //bottom right

            Vec2d n0 = new Vec2d(x0, y0);
            Vec2d n1 = new Vec2d(x1, y0);
            Vec2d n2 = new Vec2d(x1, y1);
            Vec2d n3 = new Vec2d(x0, y1);

            //--get distance vectors to nodes
            Vec2d d0 = CalculateDistanceVector(n0, x, y);
            Vec2d d1 = CalculateDistanceVector(n1, x, y);
            Vec2d d2 = CalculateDistanceVector(n2, x, y);
            Vec2d d3 = CalculateDistanceVector(n3, x, y);

            //--get gradients at nodes
            /*
             * A   B
             * D   C
             * 
             */
            int indexA = x0 + (y0 * (_width + 1));
            int indexB = indexA + 1;
            int indexC = indexB + _width + 1;
            int indexD = indexA + _width + 1;
            Vec2d g0 = _gradients[indexA];
            Vec2d g1 = _gradients[indexB];
            Vec2d g2 = _gradients[indexC];
            Vec2d g3 = _gradients[indexD];

            //--calculate dot products
            double dot0 = d0.Dot(g0);
            double dot1 = d1.Dot(g1);
            double dot2 = d2.Dot(g2);
            double dot3 = d3.Dot(g3);

            double dx = x - x0;
            double dy = y - y0;

            //--lerpy
            double a = Lerp(dot0, dot1, dx);
            double b = Lerp(dot3, dot2, dx);
            double c = Lerp(a, b, dy);

            return c;
        }

        private Vec2d CalculateDistanceVector(Vec2d node, double x, double y)
        {
            Vec2d vec = new Vec2d(node.X - x, node.Y - y);
            return vec;
        }

        private void InitGradients()
        {
            Random random = new Random(31);

            for(int i = 0; i <= _height; i++)
            {
                for(int j = 0; j <= _width; j++)
                {                    
                    double x = (random.NextDouble() + 1.0) - 1.0;
                    double y = (random.NextDouble() + 1.0) - 1.0;

                    Vec2d v = new Vec2d(x, y);
                    v.Normalize();

                    _gradients.Add(v);
                }
            }
        }

        private double Lerp(double a, double b, double w)
        {
            w = Smooth(w);

            double lerp = 0;

            lerp = (w * (b - a)) + a;

            return lerp;
        }

        private double Smooth(double w)
        {
            //6x^{5}-15x^{4}+10x^{3}
            if(w < 0)
            {
                return 0;
            }
            if(w > 1)
            {
                return 1;
            }

            double smooth = (6 * w * w * w * w * w * w) - (15 * w * w * w * w) + (10 * w * w * w);

            return smooth;
        }
    }
}
