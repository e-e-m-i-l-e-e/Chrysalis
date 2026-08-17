#include "CLOAPIInterface.h"

using namespace CLOAPI;

APICommand::APICommand() :
    m_ExportAPIInterface(nullptr), m_ImportAPIInterface(nullptr), m_RestAPIInterface(nullptr),
    m_UtilityAPIInterface(nullptr), m_FabricAPIInterface(nullptr), m_PatternAPIInterface(nullptr) {}

APICommand::~APICommand() {}

APICommand& APICommand::getInstance() {
    static APICommand instance;
    return instance;
}

void APICommand::destroy() {}

void APICommand::SetExportAPI(ExportAPIInterface* _interface) {
    m_ExportAPIInterface = _interface;
}

void APICommand::SetImportAPI(ImportAPIInterface* _interface) {
    m_ImportAPIInterface = _interface;
}

void APICommand::SetRestAPI(RestAPIInterface* _interface) {
    m_RestAPIInterface = _interface;
}

void APICommand::SetUtilityAPI(UtilityAPIInterface* _interface) {
    m_UtilityAPIInterface = _interface;
}

void APICommand::SetFabricAPI(FabricAPIInterface* _interface) {
    m_FabricAPIInterface = _interface;
}

void APICommand::SetPatternAPI(PatternAPIInterface* _interface) {
    m_PatternAPIInterface = _interface;
}

ExportAPIInterface* APICommand::GetExportAPI() {
    return m_ExportAPIInterface;
}

ImportAPIInterface* APICommand::GetImportAPI() {
    return m_ImportAPIInterface;
}

RestAPIInterface* APICommand::GetRestAPI() {
    return m_RestAPIInterface;
}

UtilityAPIInterface* APICommand::GetUtilityAPI() {
    return m_UtilityAPIInterface;
}

FabricAPIInterface* APICommand::GetFabricAPI() {
    return m_FabricAPIInterface;
}

PatternAPIInterface* APICommand::GetPatternAPI() {
    return m_PatternAPIInterface;
}
