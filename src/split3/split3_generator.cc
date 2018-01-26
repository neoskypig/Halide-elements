#include <cstdint>
#include "Halide.h"
#include "Element.h"

using namespace Halide;
using Halide::Element::schedule;

template<typename T>
class Split3 : public Halide::Generator<Split3<T>> {
public:
    ImageParam src{type_of<T>(), 3, "src"};

    GeneratorParam<int32_t> width{"width", 1024};
    GeneratorParam<int32_t> height{"height", 768};

    Func build() {
        Func dst;
        dst = Element::split3(src, width, height);
        
        schedule(src, {width, height, 3});
        schedule(dst, {width, height});
        return dst;
    }
};

RegisterGenerator<Split3<uint8_t>> split3_u8{"split3_u8"};
RegisterGenerator<Split3<uint16_t>> split3_u16{"split3_u16"};
RegisterGenerator<Split3<int8_t>> split3_i8{"split3_i8"};
RegisterGenerator<Split3<int16_t>> split3_i16{"split3_i16"};
