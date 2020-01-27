/*
* Copyright (c) 2019-2020, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#include "cudaaligner_test_cases.hpp"

#include <random>
#include "../src/needleman_wunsch_cpu.hpp"
#include <claragenomics/utils/genomeutils.hpp>

namespace
{

constexpr int32_t n_random_testcases  = 10;
constexpr int32_t max_sequence_length = 5000;
constexpr uint32_t random_seed        = 5827349;

claragenomics::TestCaseData generate_random_test_case(std::minstd_rand& rng)
{
    using claragenomics::get_size;
    claragenomics::TestCaseData t;
    std::uniform_int_distribution<int> random_length(0, max_sequence_length);
    t.target                                  = claragenomics::genomeutils::generate_random_genome(random_length(rng), rng);
    t.query                                   = claragenomics::genomeutils::generate_random_sequence(t.target, rng, get_size(t.target), get_size(t.target), get_size(t.target));
    claragenomics::cudaaligner::matrix<int> s = claragenomics::cudaaligner::needleman_wunsch_build_score_matrix_naive(t.target, t.query);
    t.edit_distance                           = s(s.num_rows() - 1, s.num_cols() - 1);
    return t;
}
} // namespace

namespace claragenomics
{
std::vector<TestCaseData> create_cudaaligner_test_cases()
{
    std::vector<TestCaseData> tests;

    TestCaseData t;

    t.target        = "AAAAAAAAAA";
    t.query         = "CGTCGTCGTC";
    t.edit_distance = 10;
    tests.push_back(t);

    t.target        = "AATAATAATA";
    t.query         = "CGTCGTCGTC";
    t.edit_distance = 7;
    tests.push_back(t);

    t.target        = "AATAATAATA";
    t.query         = "";
    t.edit_distance = 10;
    tests.push_back(t);

    t.target        = "";
    t.query         = "CGTCGTCGTC";
    t.edit_distance = 10;
    tests.push_back(t);

    t.target        = "AATAATAATA";
    t.query         = "C";
    t.edit_distance = 10;
    tests.push_back(t);

    t.target        = "CGTCGTCGTC";
    t.query         = "CGTCGTCGTC";
    t.edit_distance = 0;
    tests.push_back(t);

    t.target        = "CGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGT";
    t.query         = "AGTCGTCGTCCGTAATCGTCCGTCGTCGTCGA";
    t.edit_distance = 4;
    tests.push_back(t);

    t.target        = "CGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTC";
    t.query         = "AGTCGTCGTCCGTAATCGTCCGTCGTCGTCGTA";
    t.edit_distance = 4;
    tests.push_back(t);

    t.target        = "GTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTCGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTCGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTC";
    t.query         = "GTCGTCGTCCGTCGTCGTCCGTCGTCGTCGAAAACGTCGTCCGTCGTCGTCCGTCGTCGAAAACGTCGTCGTCCGTAGTCGTCCGACGTCGTCGTC";
    t.edit_distance = 10;
    tests.push_back(t);

    t.target        = "GTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTCGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTCGTCGTCGTCCGTCGTCGTCCGTCGTCGTCGTC";
    t.query         = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    t.edit_distance = 96;
    tests.push_back(t);

    std::minstd_rand rng(random_seed);
    for (int32_t i = 0; i < n_random_testcases; ++i)
        tests.push_back(generate_random_test_case(rng));
    return tests;
}
} // namespace claragenomics