#include "fetcher.hpp"

uint8_t twos_complement(uint8_t val)
{
    return -(unsigned int)val;
}

bool Record::loadNextRecord(std::fstream &input)
{
    std::string line;
    getline(input, line);

    if(line.size() == 0)
        return 1;

    if (line.at(0) != ':')
        throw std::runtime_error("HEX Format error!");

    Record inbound;
    inbound.record_length = std::stoi(line.substr(1, 2), 0, 16);
    inbound.address = std::stoi(line.substr(3, 4), 0, 16);
    inbound.type = std::stoi(line.substr(7, 2), 0, 16);

    uint8_t checksum = inbound.record_length + inbound.address + inbound.type;
    for (int i = 0; i < inbound.record_length * 2; i += 4)
    {
        Instruction instruction;

        instruction.opcode = std::stoi(line.substr(9 + i + 2, 2), 0, 16);
        instruction.arg = std::stoi(line.substr(9 + i, 2), 0, 16);
        instruction_data.push_back(std::move(instruction));
        checksum += instruction.opcode + instruction.arg;
    }

    inbound.checksum = std::stoi(line.substr(line.length() - 3, 2), 0, 16);

    if (inbound.checksum != twos_complement(checksum))
        throw std::runtime_error("Checksum miss-match in hex file!");

    return true;
}

