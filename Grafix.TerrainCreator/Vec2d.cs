using System;
using System.Collections.Generic;
using System.Text;

namespace Grafix.TerrainCreator
{
    struct Vec2d
    {
        public double x;
        public double y;
        public string DEBUG;

        public Vec2d(double x, double y, string debug = "")
        {
            this.x = x;
            this.y = y;
            this.DEBUG = debug;
        }

        public void Normalize()
        {
            double magnitude = Math.Sqrt((x * x) + (y * y));
            if (magnitude > 0)
            {
                this.x = this.x / magnitude;
                this.y = this.y / magnitude;
            }
        }   
        
        public double Dot(Vec2d vec)
        {
            return (vec.x * this.x) + (vec.y * this.y);
        }
    }

}
