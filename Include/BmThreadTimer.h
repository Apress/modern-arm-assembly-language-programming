#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <vector>
#include "OS.h"

class BmThreadTimer
{
    size_t m_NumIter;
    size_t m_NumAlg;
    std::vector<std::chrono::high_resolution_clock::time_point> m_StartTime;
    std::vector<std::chrono::high_resolution_clock::time_point> m_StopTime;

public:

    enum class EtUnit
    {
        NanoSec,
        MicroSec,
        MilliSec,
        Sec
    };

    BmThreadTimer(void) = delete;
    
    BmThreadTimer(size_t num_iter, size_t num_alg)
    {
        m_NumIter = num_iter;
        m_NumAlg = num_alg;

        std::vector<std::chrono::high_resolution_clock::time_point> start_time(num_iter * num_alg);
        std::vector<std::chrono::high_resolution_clock::time_point> stop_time(num_iter * num_alg);
        m_StartTime = std::move(start_time);
        m_StopTime = std::move(stop_time);
    }

    ~BmThreadTimer()
    {
    }

    BmThreadTimer(const BmThreadTimer& bmtt) = delete;
    BmThreadTimer(BmThreadTimer&& bmtt) = delete;
    BmThreadTimer& operator = (const BmThreadTimer& bmtt) = delete;
    BmThreadTimer& operator = (BmThreadTimer&& bmtt) = delete;

    static std::string BuildCsvFilenameString(const std::string& prefix, const std::string& base_name1, const std::string& base_name2)
    {
        std::string fn = prefix + base_name1;
        std::string computer_name = OS::GetComputerName();

        if (base_name2 != "")
        {
            fn += '_';
            fn += base_name2;
        }

        if (computer_name != "")
        {
            fn += '_';
            fn += computer_name;
        }

        fn += ".csv";
        return fn;
    }

    static std::string BuildCsvFilenameString(const std::string& base_name1)
    {
        return BmThreadTimer::BuildCsvFilenameString("", base_name1, "");
    }

    void SaveElapsedTimes(const std::string& fn, EtUnit et_unit, int p)
    {
        std::ofstream ofs(fn);

        ofs << std::fixed << std::setprecision(p);

        if (ofs.is_open())
        {
            for (size_t i = 0; i < m_NumIter; i++)
            {
                for (size_t j = 0; j < m_NumAlg; j++)
                {
                    std::chrono::high_resolution_clock::time_point t_start = m_StartTime[i * m_NumAlg + j];
                    std::chrono::high_resolution_clock::time_point t_stop = m_StopTime[i * m_NumAlg + j];
                    std::chrono::duration<double> et = std::chrono::duration_cast<std::chrono::duration<double>>(t_stop - t_start);

                    switch (et_unit)
                    {
                        case EtUnit::NanoSec:
                            et *= 1.0e9;
                            break;
    
                        case EtUnit::MicroSec:
                            et *= 1.0e6;
                            break;

                        case EtUnit::MilliSec:
                            et *= 1.0e3;
                            break;

                        case EtUnit::Sec:
                            break;

                        default:
                            throw std::runtime_error("BmThreadTimer::SaveElapsedTimes() - Invalid EtUint");
                    }

                    ofs << et.count();

                    if (j + 1 < m_NumAlg)
                        ofs << ", ";
                    else
                        ofs << '\n';
                }
            }

            ofs.close();
        }
        else
            throw std::runtime_error("BmThreadTimer::SaveElapsedTimes() - File open error");
    }

    void Start(size_t iter_id, size_t alg_id)
    {
        m_StartTime[iter_id * m_NumAlg + alg_id] = std::chrono::high_resolution_clock::now();
    }

    void Stop(size_t iter_id, size_t alg_id)
    {
        m_StopTime[iter_id * m_NumAlg + alg_id] = std::chrono::high_resolution_clock::now();
    }
};
