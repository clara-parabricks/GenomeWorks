/*
* Copyright 2020 NVIDIA CORPORATION.
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
#pragma once

#include <claraparabricks/genomeworks/utils/cudautils.hpp>
#include "ungapped_xdrop.cuh"

namespace claraparabricks
{

namespace genomeworks
{

namespace cudaextender
{

// extend the hits to a segment by ungapped x-drop method, adjust low-scoring
// segment scores based on entropy factor, compare resulting segment scores
// to hspthresh and update the d_hsp and d_done vectors
__global__ void find_high_scoring_segment_pairs(const char* __restrict__ d_target, const int32_t target_length, const char* __restrict__ d_query, const int32_t query_length, const int32_t * d_sub_mat, bool no_entropy, int32_t xdrop_threshold, int32_t score_threshold, SeedPair* d_seed_pairs, int32_t num_seed_pairs, int32_t start_index, ScoredSegmentPair* d_scored_segment, int32_t* d_done);

// gather only the HSPs from the resulting segments to the beginning of the
// tmp_hsp vector
__global__ void compress_output(int32_t* d_done, int32_t start_index, ScoredSegmentPair * d_hsp, ScoredSegmentPair* d_tmp_hsp, int num_hits);

// Binary Predicate for sorting the ScoredSegmentPairs
struct scored_segment_pair_comp
{
    __host__ __device__ bool operator()(ScoredSegmentPair x, ScoredSegmentPair y)
    {
        if (x.seed_pair.query_position_in_read < y.seed_pair.query_position_in_read)
            return true;
        else if (x.seed_pair.query_position_in_read == y.seed_pair.query_position_in_read)
        {
            if (x.length > y.length)
                return true;
            else if (x.length == y.length)
            {
                if (x.seed_pair.target_position_in_read < y.seed_pair.target_position_in_read)
                    return true;
                else if (x.seed_pair.target_position_in_read == y.seed_pair.target_position_in_read)
                {
                    if (x.score > y.score)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
};

struct scored_segment_pair_equal
{
    __host__ __device__ bool operator()(ScoredSegmentPair x, ScoredSegmentPair y)
    {
        return ((x.seed_pair.target_position_in_read == y.seed_pair.target_position_in_read) && (x.seed_pair.query_position_in_read == y.seed_pair.query_position_in_read) && (x.length == y.length) && (x.score == y.score));
    }
};

} // namespace cudaextender

} // namespace genomeworks

} // namespace claraparabricks