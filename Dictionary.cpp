#include "Dictionary.h"

namespace Dict {

    QString getWordMeaning(QStringView str) {
        return "Meaning of " + str.toString();
    };

}