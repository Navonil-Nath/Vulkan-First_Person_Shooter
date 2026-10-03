#include"shaderModule.hpp"
#include<fstream>



ShaderModule::ShaderModule(VkDevice device,std::string& filePath):m_device(device){
    auto code=ReadFile(filePath);
    CreateShaderModule(code);

}


ShaderModule::~ShaderModule(){
    if(m_shaderModule!=VK_NULL_HANDLE){
        vkDestroyShaderModule(m_device,m_shaderModule,nullptr);
    }

}

std::vector<char>ShaderModule::ReadFile(std::string& filepath){

    std::ifstream file(filepath,std::ios::ate | std::ios::binary);
    //this above pointer sets the pointer to the spv file and sets it to the end of the file ie to the end bit
    //the std::ios::ste means to the end and the std::ios::binary means the type of data we are dealing with is binary

    if(!file.is_open()){
        throw std::runtime_error("the sv file coudn't be read");
    }
    size_t fileSize=static_cast<size_t>(file.tellg());

    std::vector<char>buffer(fileSize); //this shall contain all the data of the spv file

    file.seekg(0); //set th pointer to the start of the spv file again
    file.read(buffer.data(),fileSize); //afer pointing to thefirst bit read thecontents of the file to the buffer vector of characters
     return buffer;

}


void ShaderModule::CreateShaderModule(const std::vector<char>& code){

    VkShaderModuleCreateInfo createInfo{};

    createInfo.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize=code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*> (code.data()); //getting the character binaries converted to the numeric binaries


    if(vkCreateShaderModule(m_device,&createInfo,nullptr,&m_shaderModule)!=VK_SUCCESS){
        throw std::runtime_error("the shader module coudn't be created");
    }

}



