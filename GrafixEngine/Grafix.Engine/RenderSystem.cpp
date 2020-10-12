#include "RenderSystem.h"

bool RenderSystem::Init()
{
    Application* app = Application::Current();    
    DeviceResources* res = app->Resources;       

    return false;
}

void RenderSystem::Frame(Scene* scene)
{
    Application* app = Application::Current();
    DeviceResources* res = app->Resources;

    //iterate over the entities and process the rendering components

    for (int i = 0; i < Grafix::MAX_ENTITIES; i++)
    {
        int entityID = i;

        RenderingComponent* rc = scene->Entities->RenderingComponents[entityID];

        //res->Context->IASetInputLayout
        //res->Context->IAGetPrimitiveTopology
        //res->Context->IASetVertexBuffers
        //res->Context->IASetIndexBuffer

        //res->Context->VSSetShader
        //res->Context->VSSetConstantBuffers        
                
        //res->Context->RSSetState        

        //res->Context->PSSetShader
        //res->Context->PSSetConstantBuffers        
    }
}
