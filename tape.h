#ifndef YADRO_TEST_TAPE_H
#define YADRO_TEST_TAPE_H

#include <vector>
#include "tape-abstract.h"
#include "Delays.h"

class Tape : public TapeAbstract{
public:
    enum class Cond {
        OPEN_EXIST,
        CREATE_IF_MISSING,
        CREATE_OR_OVERWRITE
    };
    Tape(std::string filename, size_t length, const Delays& delays, Cond cond);
    virtual ~Tape() = default;

    size_t read() override;

    void write(size_t value) override;

    void moveForward() override;

    void moveBack() override;

    void rewind() override;

    size_t length() override;

    size_t index() override;

private:
    const std::string _filename;
    const size_t _tape_size;
    size_t _index;
    const Delays& _delays;
    static void sleep(int time);
    void createIfMiss();
    void createOrOverwrite();
    void createFile();
    void openExist();
    void throwIfEmpty(std::ifstream& file);
    void fillWithZeros(std::ofstream& newFile) const;
    std::vector<int> data;
};


#endif //YADRO_TEST_TAPE_H
