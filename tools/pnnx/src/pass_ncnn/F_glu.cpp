// Copyright (c) 2022 Xiaomi Corp.        (author: Fangjun Kuang)
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#include "pass_ncnn.h"

namespace pnnx {

namespace ncnn {

class F_glu : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
3 2
pnnx.Input           input          0 1 input
F.glu                op_0           1 1 input out dim=%dim
pnnx.Output          output         1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "GLU";
    }

    const char* name_str() const
    {
        return "glu";
    }
    void write(Operator* op,
               const std::map<std::string, Parameter>& captured_params) const
    {
        int axis = captured_params.at("dim").i;

        op->params["0"] = axis;
    }
};

REGISTER_GLOBAL_PNNX_NCNN_GRAPH_REWRITER_PASS(F_glu, 20)

} // namespace ncnn

} // namespace pnnx
