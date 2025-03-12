#include <concepts>
#include <memory>
#include <span>
#include <iostream>
#include <vector>

template<class T>
concept InPlaceProcessor = requires (T p){
    p.Process(std::span<float>{}); // Note the instantiation of unit {}
};

// WrappedProcessor only compiles if instantiated with a ProcessorType that has the Process
// method as stipulated by the InPlaceProcessor concept
template<InPlaceProcessor ProcessorType>
class WrappedProcessor{
    public:
    WrappedProcessor(std::shared_ptr<ProcessorType> processor){
        m_processor = processor;
    }
    void Process(std::span<float> buf){
        m_processor->Process(buf);
    }

    // Reset will be compiled into target only if ProcessorType has
    // a reset method
    void Reset() requires requires (ProcessorType p) {p.Reset();} {
        m_processor->Reset();
    }

    private:
    std::shared_ptr<ProcessorType> m_processor;

};

int main(){
    struct TestProcessor{
        bool Process(std::span<float> input){
            std::cout<< "Length of input is " << input.size() << std::endl;
            return true;
        }
    };

    auto testProcessorObj = std::make_shared<TestProcessor>();

    WrappedProcessor<TestProcessor> wrappedProc(testProcessorObj);

    std::vector<float> inVec{1.0f, 2.0f, 3.0f};
    wrappedProc.Process(inVec);
    return 0;
}