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

#include <claraparabricks/genomeworks/cudamapper/cudamapper.hpp>
#include <claraparabricks/genomeworks/logging/logging.hpp>

namespace claraparabricks
{

namespace genomeworks
{

namespace cudamapper
{

namespace cudamapper
{

StatusType Init()
{
    initialize_logger(claraparabricks::genomeworks::logging::LogLevel::warn);
    return StatusType::success;
}

} // namespace cudamapper
} // namespace cudamapper

} // namespace genomeworks

} // namespace claraparabricks
