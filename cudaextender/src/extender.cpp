/*
* Copyright 2019-2020 NVIDIA CORPORATION.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <claraparabricks/genomeworks/cudaextender/extender.hpp>

#include "ungapped_xdrop.cuh"

namespace claraparabricks
{

namespace genomeworks
{

namespace cudaextender
{

std::unique_ptr<Extender> create_extender(int32_t* h_sub_mat, int32_t sub_mat_dim, int32_t xdrop_threshold, bool no_entropy, cudaStream_t stream, int32_t device_id, ExtensionType type)
{
    if (type == ExtensionType::ungapped_xdrop)
    {
        return std::make_unique<UngappedXDrop>(h_sub_mat, sub_mat_dim, xdrop_threshold, no_entropy, stream, device_id);
    }
    else
    {
        throw std::runtime_error("Extender for specified type not implemented yet.");
    }
}

} // namespace cudaextender

} // namespace genomeworks

} // namespace claraparabricks