using System;
using System.Collections.Generic;
using System.Text;

namespace Grafix.TerrainCreator
{
    public class Perlin2
    {
        private int _width;
        private int _height;
        private int _maxWidth;
        private int _maxHeight;

        private List<Vec2d> _gradients;

        public Perlin2(int width, int height, int maxWidth, int maxHeight)
        {
            _width = width;
            _height = height;
            _maxWidth = maxWidth;
            _maxHeight = maxHeight;

            InitGradients();
        }

        //--public
        public double Noise(double x, double y)
        {
            //--find the coordinates into the gradient grid
            double cellX = ((x / (_maxWidth * 1.0)) * _width);
            double cellY = ((y / (_maxHeight * 1.0)) * _height);
            int nodeX = (int)(cellX);
            int nodeY = (int)(cellY);
            double dx = cellX - nodeX; // this puts the value between 0-1 for that cell "pixel"
            double dy = cellY - nodeY;

            //--find index into array
            /*
             * lets assume the grid is 3 rows x 3 columns
             * assume gradientX = 1
             * assume gradientY = 0
             * 
             * this is saying row 1 column 0, but we know that would be index 3
             * 
             * assume gradientX = 2 //row 3
             * and gradientY = 2 //column 3
             * 
             * general form
             * index = (gradientX * _width) + gradientY
             */
            //int gradientIndex = (nodeX * _width) + nodeY;
            int gradientIndex = (nodeY * (_height + 1)) + nodeX;

            /*
             * A    B
             * D     C
             * 
             */

            int aIndex = gradientIndex;
            int bIndex = gradientIndex + 1;
            int cIndex = (gradientIndex + 1) + _width + 1;
            int dIndex = gradientIndex + _width + 1;

            //--calculate distance vectors and dot them with gradients
            Vec2d node0 = new Vec2d(nodeX, nodeY); //top left
            Vec2d node1 = new Vec2d(nodeX + 1, nodeY); //top right
            Vec2d node2 = new Vec2d(nodeX + 1, nodeY + 1); //bottom right
            Vec2d node3 = new Vec2d(nodeX, nodeY + 1); //bottom left
            //Vec2d node0 = new Vec2d(0, 0); //top left
            //Vec2d node1 = new Vec2d(1, 0); //top right
            //Vec2d node2 = new Vec2d(1, 1); //bottom right
            //Vec2d node3 = new Vec2d(0, 1); //bottom left

            //node0.Normalize();
            //node1.Normalize();
            //node2.Normalize();
            //node3.Normalize();

            Vec2d distance0 = CalculateDistanceVector(node0, cellX, cellY);
            Vec2d distance1 = CalculateDistanceVector(node1, cellX, cellY);
            Vec2d distance2 = CalculateDistanceVector(node2, cellX, cellY);
            Vec2d distance3 = CalculateDistanceVector(node3, cellX, cellY);

            //distance0.Normalize();
            //distance1.Normalize();
            //distance2.Normalize();
            //distance3.Normalize();

            Vec2d grad0 = _gradients[aIndex];
            Vec2d grad1 = _gradients[bIndex];
            Vec2d grad2 = _gradients[cIndex];
            Vec2d grad3 = _gradients[dIndex];

            double dot0 = distance0.Dot(grad0);
            double dot1 = distance1.Dot(grad3);
            double dot2 = distance2.Dot(grad2);
            double dot3 = distance3.Dot(grad1);

            //--interpolate
            double a = Lerp(dot0, dot1, dx);
            double b = Lerp(dot2, dot3, dx);
            double c = Lerp(a, b, dy);

            return c;
        }

        //--private
        private void InitGradients()
        {
            _gradients = new List<Vec2d>();

            Random r = new Random(5);

            //int c = (_width + 1) * (_height + 1);
            //int degrees = 0;
            //int index = 0;
            //while(index < c)
            //{
            //    Vec2d v;
            //    v.x = Math.Cos(degrees * (Math.PI / 180.0));
            //    v.y = Math.Sin(degrees * (Math.PI / 180.0));
            //    v.DEBUG = $"";

            //    v.Normalize();

            //    _gradients.Add(v);
            //    ++index;
            //    ++degrees;
            //}

            //for(int i = 0; i < c; i++)
            //{
            //    Vec2d v;                
            //    v.DEBUG = $"";
            //    v.x = Math.Cos(i * (Math.PI / 180.0));
            //    v.y = Math.Sin(i * (Math.PI / 180.0));

            //    v.Normalize();

            //    _gradients.Add(v);
            //}            

            for (int i = 0; i <= _width; i++)
            {
                for (int j = 0; j <= _height; j++)
                {
                    Vec2d v;
                    v.x = (r.NextDouble() * 2.0) - 1.0;
                    v.y = (r.NextDouble() * 2.0) - 1.0;
                    v.DEBUG = $"{i},{j}";

                    v.Normalize();

                    _gradients.Add(v);
                }
            }
        }

        private Vec2d CalculateDistanceVector(Vec2d node, double normalizedCellX, double normalizedCellY)
        {
            //double dx = normalizedCellX - node.x;
            //double dy = normalizedCellY - node.y;

            //double distance = Math.Sqrt((dx * dx) + (dy * dy));

            Vec2d distanceVec;
            //distanceVec.x = normalizedCellX - node.x;
            //distanceVec.y = normalizedCellY - node.y;
            distanceVec.x = node.x - normalizedCellX;
            distanceVec.y = node.y - normalizedCellY;
            distanceVec.DEBUG = "";

            return distanceVec;
        }

        private double Lerp(double a, double b, double w)
        {
            //return ((1 - w) * a) + (w * b);

            double lerp = 0;

            w = Smooth(w);

            lerp = (w * (b - a)) + a;

            return lerp;
        }

        private double Smooth(double w)
        {
            double a = 3.5;
            double b = 10;
            double e = Math.E;

            double smooth = (Math.Pow(e, -w) - Math.Pow(e, -a * w)) / (Math.Pow(e, w) + Math.Pow(e, -b * w));

            return smooth;
        }
    }
}
