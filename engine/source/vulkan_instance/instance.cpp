#include"instance.hpp"
#include<stdexcept>
#include<cstdlib>


namespace{
    //this shall contain some local-only functions
    const std::vector<const char*>validationLayers={"VK_LAYER_KHRONOS_validation"};

    //the callback function which will be called by the setUpDebugMessenger
    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){

        if(messageSeverity== VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
            throw std::runtime_error(pCallbackData->pMessage);
        }
        else{
            std::cout<<"[Validation layer:]"<<pCallbackData->pMessage<<std::endl;
        }
        return VK_FALSE;
    }


    //--second function---
    void DestroyDebugUtilsMessengerEXT(VkInstance instance,VkDebugUtilsMessengerEXT debugMessenger,const VkAllocationCallbacks* pAllocator){
        auto func=(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance,"vkDebugUtilsMessengerEXT");
        //chekingif the instance level func is loaded to prevent craches
        if(func!=nullptr){
            func(instance,debugMessenger,pAllocator);
        }

    }

    //-----third_function----

    //this function shall create the debug callback function that will communicate with the vulkan drivers and our application
    //this below should be aproxy functionthat calls the "vkCreateDebugUtilsMessengerEXT" function!!
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,const VkAllocationCallbacks* pAllocator,VkDebugUtilsMessengerEXT* pDebugMessenger){
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance,"vkCreateDebugUtilsMessengerEXT");

        if(func!=nullptr){
            return func(instance,pCreateInfo,pAllocator,pDebugMessenger);
        }
        else{
            throw std::runtime_error("reuired validation layer-> debug callback funtion extension not found");
        }
    }


}//namespace

VulkanInstance::VulkanInstance(const std::string& appName){

    CreateInstance(appName);
    setUpDebugMessenger();
}

VulkanInstance::~VulkanInstance(){
    if( m_debugMessenger!=VK_NULL_HANDLE){
        DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger,nullptr);
    }
    if(m_instance!=VK_NULL_HANDLE){
        vkDestroyInstance(m_instance,nullptr);
    }
}


bool VulkanInstance::checkValidationLayerSupport(){
    uint32_t layerCount=0;
    vkEnumerateInstanceLayerProperties(&layerCount,nullptr);
    std::vector<VkLayerProperties>availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount,availableLayers.data());
    bool layerPresent=false;
    for(const char* layerName:validationLayers){
        
        for(auto& layerProperties:availableLayers){
            if(strcmp(layerName,layerProperties.layerName)==0){
                layerPresent=true;
                break;
            }
        }

    }
    if(layerPresent==false){
        return false;
    }
    else{
        return true;
    }

}

std::vector<const char*> VulkanInstance::getRequiredGlfwExtensions(){
    //get the glfw related extensions
    uint32_t glfwExtensionsCount=0;
    const char** glfwExtensions=glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
    std::vector<const char*>extensions(glfwExtensions,glfwExtensions+glfwExtensionsCount);

    if(checkValidationLayerSupport()){
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;

}
void VulkanInstance::CreateInstance(const std::string& appName){
    

    //now with everythin g ready lets move to creating the instance
    bool enableValidation=checkValidationLayerSupport();
     VkApplicationInfo appInfo{};
     appInfo.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
     appInfo.pApplicationName=appName.c_str();
     appInfo.applicationVersion=VK_MAKE_VERSION(1,0,0);
     appInfo.pEngineName="Kitten_Engine";
     appInfo.engineVersion=VK_MAKE_VERSION(1,0,0);
     appInfo.apiVersion=VK_API_VERSION_1_3;
     

     //get all the extensions of the glfw
     auto extensions=getRequiredGlfwExtensions();

     VkInstanceCreateInfo createInfo{};
     createInfo.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
     createInfo.pApplicationInfo=&appInfo;
     createInfo.enabledExtensionCount=static_cast<uint32_t>(extensions.size());
     createInfo.ppEnabledExtensionNames=extensions.data();
     
     if(enableValidation){
        createInfo.enabledLayerCount=static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames=validationLayers.data();
     }
     else{
        createInfo.enabledLayerCount=0;
     }
     if(vkCreateInstance(&createInfo,nullptr,&m_instance)!=VK_SUCCESS){
        throw std::runtime_error("the vulkaninstance coudn't be initated");
     }
}

void VulkanInstance::setUpDebugMessenger(){ //it will call the 'debugCallback()' function internally

    //here in the VulkanInstance() cinstructor the setUpDebugMessenger func is called immediatelly after the 
    //call to the createInstance() this automatically attaches the debugCallback() to the m_instance which 
    //is a vulkan architechtural system

    if(!checkValidationLayerSupport()){
        std::cout<<"the validation layers can't be included"<<std::endl;
        return;
    }
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity=VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType=VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback=&debugCallback;
    createInfo.pUserData=nullptr;

    if(CreateDebugUtilsMessengerEXT(m_instance,&createInfo,nullptr,&m_debugMessenger)!=VK_SUCCESS){
        std::cerr<<"[Vulkan validation]:"<<"falilled to set up vulkan validation layer setup"<<std::endl;
    } 
    else{
        std::cout<<"validation layer set upped correctlly"<<std::endl;
    }

}




