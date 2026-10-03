#ifndef SHADER_MODULE_CLASS
#define SHADER_MODULE_CLASS
#include<stdexcept>
#include<iostream>
#include<vulkan/vulkan.h>
#include<cstdlib>
#include<array>
#include<vector>
#include<string>

class ShaderModule{
    public: 
    ShaderModule(VkDevice device,std::string& filePath);
    ~ShaderModule();

    ShaderModule(const ShaderModule&)=delete;
    ShaderModule& operator=(const ShaderModule&)=delete;


    private:    
    VkDevice m_device{VK_NULL_HANDLE};
    VkShaderModule m_shaderModule{VK_NULL_HANDLE};
    static std::vector<char>ReadFile(std::string& filePath); //this will load the bytecode form the disk to a vector 
    void CreateShaderModule(const std::vector<char>& code);
};

#endif