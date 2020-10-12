#include "Perlin.h"

void Perlin::Init(int width, int height)
{
    //0 - random gradients and assign values
    _randomGradients.push_back(DirectX::XMFLOAT2(0, 1));
    _randomGradients.push_back(DirectX::XMFLOAT2(1, 0));
    _randomGradients.push_back(DirectX::XMFLOAT2(1, 1));
    _randomGradients.push_back(DirectX::XMFLOAT2(0, -1));
    _randomGradients.push_back(DirectX::XMFLOAT2(-1, 0));
    _randomGradients.push_back(DirectX::XMFLOAT2(-1, -1));
    _maxHeight = height;
    _maxWidth = width;

    //1 - grid definition
    srand(time(0));
    int maxGradientIndex = _randomGradients.size();

    //add vertical then horizontal    
    for (int x = 0; x <= height; x++)
    {
        for (int y = 0; y <= height; y++)
        {
            int index = rand() % maxGradientIndex;
            DirectX::XMFLOAT2 gradient = _randomGradients[index];

            _grid.push_back(gradient);
        }
    }


}

double Perlin::Noise(double x, double y)
{
    // translate into gridX and gridY
    double scaledX = x * (_maxWidth - 1);
    double scaledY = y * (_maxHeight - 1);

    // get grid indexes and gradients and distant vectors
    int gridX = (int)scaledX;
    int gridY = (int)scaledY;
    int siblingX = gridX + 1;
    int siblingY = gridY + 1;
    double normX = 1 - (siblingX - scaledX);
    double normY = 1 - (siblingY - scaledY);
    DirectX::XMFLOAT2 normPoint = DirectX::XMFLOAT2(normX, normY);

    int ia = GetGridVectorOffset(gridX, gridY);
    int ib = GetGridVectorOffset(gridX, gridY + 1);
    int ic = GetGridVectorOffset(gridX + 1, gridY);
    int id = GetGridVectorOffset(gridX + 1, gridY + 1);

    DirectX::XMFLOAT2 gradientA = _grid[ia];
    DirectX::XMFLOAT2 gradientB = _grid[ib];
    DirectX::XMFLOAT2 gradientC = _grid[ic];
    DirectX::XMFLOAT2 gradientD = _grid[id];

    DirectX::XMFLOAT2 nodeA = DirectX::XMFLOAT2(0, 0);
    DirectX::XMFLOAT2 nodeB = DirectX::XMFLOAT2(0, 1);
    DirectX::XMFLOAT2 nodeC = DirectX::XMFLOAT2(1, 0);
    DirectX::XMFLOAT2 nodeD = DirectX::XMFLOAT2(1, 1);

    DirectX::XMFLOAT2 dA = DirectX::XMFLOAT2(nodeA.x - normPoint.x, nodeA.y - normPoint.y);
    DirectX::XMFLOAT2 dB = DirectX::XMFLOAT2(nodeB.x - normPoint.x, nodeB.y - normPoint.y);
    DirectX::XMFLOAT2 dC = DirectX::XMFLOAT2(nodeC.x - normPoint.x, nodeC.y - normPoint.y);
    DirectX::XMFLOAT2 dD = DirectX::XMFLOAT2(nodeD.x - normPoint.x, nodeD.y - normPoint.y);

    //2 - dot product
    double dotA = (dA.x * gradientA.x) + (dA.y * gradientA.y);
    double dotB = (dB.x * gradientB.x) + (dB.y * gradientB.y);
    double dotC = (dC.x * gradientC.x) + (dC.y * gradientC.y);
    double dotD = (dD.x * gradientD.x) + (dD.y * gradientD.y);

    //3 - interpolation / smooth
    double a = LerpAndSmooth(dotA, dotC, normX);
    double b = LerpAndSmooth(dotB, dotD, normX);
    double c = LerpAndSmooth(a, b, normY);

    return c;
}

double Perlin::LerpAndSmooth(double start, double end, double factor)
{
    factor = (6 * factor * factor * factor * factor * factor) - (15 * factor * factor * factor * factor) + (10 * factor * factor * factor);

    double lerp = ((end - start) * factor) + start;

    return lerp;
}

int Perlin::GetGridVectorOffset(int x, int y)
{
    //vertical then horizontal
    int index = (x * (_maxWidth + 1)) + y;

    return index;
}
