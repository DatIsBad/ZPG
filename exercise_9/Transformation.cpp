#include "Transformation.h"
#include "Translate.h" // Required for Translate definition
#include "Rotate.h"     // Required for Rotate definition
#include "Scale.h" 

Transformation::Transformation() {

}

// Method to add a transformation using shared_ptr
void Transformation::addTransformation(const std::shared_ptr<Transformation>& transformation) {
    m_TransVector.push_back(transformation);
}

glm::mat4 Transformation::getValue() {
    glm::mat4 m_value = glm::mat4(1.0f);

    for (const auto& transformation : m_TransVector) {
        m_value = transformation->getValue() * m_value; // Apply transformations in order
    }

    return m_value;
}

void Transformation::changeTranslation(int at, const glm::vec3& newTranslation) {
    if (at >= 0 && at < m_TransVector.size()) {
        auto translatePtr = std::dynamic_pointer_cast<Translate>(m_TransVector[at]);
        if (translatePtr) {
            translatePtr->setTranslation(newTranslation);
        }
        else {
            std::cerr << "Transformation at index " << at << " is not a Translate.\n";
        }
    }
}

void Transformation::changeRotation(int at, float newAngle, const glm::vec3& newAxis) {
    if (at >= 0 && at < m_TransVector.size()) {
        auto rotatePtr = std::dynamic_pointer_cast<Rotate>(m_TransVector[at]);
        if (rotatePtr) {
            rotatePtr->setRotation(newAngle, newAxis);
        }
        else {
            std::cerr << "Transformation at index " << at << " is not a Rotate.\n";
        }
    }
}

void Transformation::changeScale(int at, const glm::vec3& newScale) {
    if (at >= 0 && at < m_TransVector.size()) {
        auto scalePtr = std::dynamic_pointer_cast<Scale>(m_TransVector[at]);
        if (scalePtr) {
            scalePtr->setScale(newScale);
        }
        else {
            std::cerr << "Transformation at index " << at << " is not a Scale.\n";
        }
    }
}

void Transformation::makeMeRotateConst(int at) {
    if (at >= 0 && at < m_TransVector.size()) {
        auto rotatePtr = std::dynamic_pointer_cast<Rotate>(m_TransVector[at]);
        if (rotatePtr) {
            rotatePtr->dynamicRotationActivate();
        }
        else {
            std::cerr << "Transformation at index " << at << " is not a Rotate.\n";
        }
    }
}


int Transformation::getSize() {
    return this->m_TransVector.size();
}
