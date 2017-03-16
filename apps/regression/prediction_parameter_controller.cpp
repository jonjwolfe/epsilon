#include "prediction_parameter_controller.h"
#include <assert.h>

using namespace Shared;

namespace Regression {

PredictionParameterController::PredictionParameterController(Responder * parentResponder, Store * store, CurveViewCursor * cursor) :
  ViewController(parentResponder),
  m_selectableTableView(SelectableTableView(this, this, 0, 1, Metric::CommonTopMargin, Metric::CommonRightMargin,
    Metric::CommonBottomMargin, Metric::CommonLeftMargin)),
  m_goToParameterController(GoToParameterController(this, store, cursor))
{
}

const char * PredictionParameterController::title() {
  return I18n::translate(I18n::Message::RegressionSlope);
}

View * PredictionParameterController::view() {
  return &m_selectableTableView;
}

void PredictionParameterController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool PredictionParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK) {
    m_goToParameterController.setXPrediction(m_selectableTableView.selectedRow() == 0);
    StackViewController * stack = (StackViewController *)parentResponder();
    stack->push(&m_goToParameterController);
    return true;
  }
  return false;
}

int PredictionParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};

HighlightCell * PredictionParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  return &m_cells[index];
}

int PredictionParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

KDCoordinate PredictionParameterController::cellHeight() {
  return Metric::ParameterCellHeight;
}

void PredictionParameterController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  MessageTableCellWithChevron * myCell = (MessageTableCellWithChevron *)cell;
  I18n::Message  titles[2] = {I18n::Message::XPrediction, I18n::Message::YPrediction};
  myCell->setMessage(titles[index]);
}

}
