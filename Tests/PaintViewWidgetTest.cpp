#include <QtTest/QtTest>
#include <QScopedPointer>
#include <QDebug>
#include <QSignalSpy>

#include "../PaintViewWidget/PaintViewWidget.h"

class TestPaintViewWidget: public QObject
{
private:
    Q_OBJECT

    QScopedPointer<PaintViewWidget> paintView;

    /* Helper methods */
    void TestStateAfterImageLoad(QImage imgToLoad);
    QImage LoadFlowerImage();

private slots:
    void initTestCase();
    void init();

    /* Methods tests */
    void TestWidgetInitialState();
    void TestLoadImage_QImage();
    void TestLoadImage_File();

    /* Slots tests */
    void TestChangePaintTool();
    void TestChangeColor();
    void TestCreateNewCanvas();
    void TestZoomIn();
    void TestZoomOut();
    void TestZoomReset();
    void TestSetZoomLevel();
    void TestFitInView();
};

void TestPaintViewWidget::initTestCase()
{
    /* called before the first test function is executed */
}

void TestPaintViewWidget::init()
{
    /* called before each test function is executed. */

    paintView.reset(new PaintViewWidget());
}

void TestPaintViewWidget::TestStateAfterImageLoad(QImage imgToLoad)
{
    QVERIFY(paintView->CanvasHeight() == imgToLoad.height());
    QVERIFY(paintView->CanvasWidth() == imgToLoad.width());
    QVERIFY(paintView->GetZoom() == 1.0);

    QImage loadedImage = paintView->GetBackground().toImage();

    QVERIFY(loadedImage == imgToLoad);
}

QImage TestPaintViewWidget::LoadFlowerImage()
{
    QImage img;
    img.load("../TestData/flower.jpg");

    paintView->LoadImage(img);

    return img;
}

void TestPaintViewWidget::TestWidgetInitialState()
{
    /* Test initial state of PaintViewWidget right after a new instance is spawned */

    QVERIFY(paintView->GetZoom() == 1.0);
    QVERIFY(paintView->CanvasHeight() == 0);
    QVERIFY(paintView->CanvasWidth() == 0);
    QVERIFY(paintView->SelectedPaintTool() == PaintTool::NN);
}

/* Methods tests */
void TestPaintViewWidget::TestLoadImage_QImage()
{
    QImage img;
    img.load("../TestData/flower.jpg");

    paintView->LoadImage(img);
    TestStateAfterImageLoad(img);
}

void TestPaintViewWidget::TestLoadImage_File()
{
    QImage img;
    img.load("../TestData/flower.jpg");

    paintView->LoadImage("../TestData/flower.jpg");
    TestStateAfterImageLoad(img);
}

/* Slots tests */
void TestPaintViewWidget::TestChangePaintTool()
{
    QSignalSpy spy(paintView.get(), &PaintViewWidget::PaintToolChanged);
    const PaintTool expectedPaintTool = PaintTool::Brush;

    paintView->ChangePaintTool(expectedPaintTool);
    QVERIFY(paintView->SelectedPaintTool() == expectedPaintTool);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).value<PaintTool>() == expectedPaintTool);
}

void TestPaintViewWidget::TestChangeColor()
{
    QSignalSpy spy(paintView.get(), &PaintViewWidget::ColorChanged);
    const QColor expectedColor = QColor::fromRgb(192, 128, 127);

    paintView->ChangeColor(expectedColor);
    QVERIFY(paintView->SelectedColor() == expectedColor);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0) == expectedColor);
}

void TestPaintViewWidget::TestCreateNewCanvas()
{
    QSignalSpy spy(paintView.get(), &PaintViewWidget::CanvasCreated);
    const int expectedWidth = 640;
    const int expectedHeight = 480;

    paintView->CreateNewCanvas(expectedWidth, expectedHeight);
    QVERIFY(paintView->CanvasHeight() == expectedHeight);
    QVERIFY(paintView->CanvasWidth() == expectedWidth);

    QCOMPARE(spy.count(), 1);
}

void TestPaintViewWidget::TestZoomIn()
{
    LoadFlowerImage();
    QSignalSpy spy(paintView.get(), &PaintViewWidget::ZoomChanged);
    const double expectedZoom = 1.0 + paintView->zoomStep;

    QVERIFY(paintView->GetZoom() == 1.0);
    paintView->ZoomIn();
    QVERIFY(paintView->GetZoom() == expectedZoom);

    qDebug() << spy;

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toDouble() == expectedZoom);
}

void TestPaintViewWidget::TestZoomOut()
{
    LoadFlowerImage();
    QSignalSpy spy(paintView.get(), &PaintViewWidget::ZoomChanged);
    const double expectedZoom = 1.0 - paintView->zoomStep;

    QVERIFY(paintView->GetZoom() == 1.0);
    paintView->ZoomOut();
    QVERIFY(paintView->GetZoom() == expectedZoom);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toDouble() == expectedZoom);
}

void TestPaintViewWidget::TestZoomReset()
{
    LoadFlowerImage();
    QSignalSpy spy(paintView.get(), &PaintViewWidget::ZoomChanged);
    const double expectedZoom = 1.0;

    QVERIFY(paintView->GetZoom() == 1.0);
    paintView->ZoomIn();
    paintView->ZoomReset();
    QVERIFY(paintView->GetZoom() == expectedZoom);

    QCOMPARE(spy.count(), 2);
    QList<QVariant> arguments = spy.at(1);
    QVERIFY(arguments.at(0).toDouble() == expectedZoom);
}

void TestPaintViewWidget::TestSetZoomLevel()
{
    LoadFlowerImage();
    QSignalSpy spy(paintView.get(), &PaintViewWidget::ZoomChanged);
    const double expectedZoom = 2.5;

    QVERIFY(paintView->GetZoom() == 1.0);
    paintView->SetZoomLevel(expectedZoom);
    QVERIFY(paintView->GetZoom() == expectedZoom);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toDouble() == expectedZoom);
}

void TestPaintViewWidget::TestFitInView()
{
    LoadFlowerImage();
}

QTEST_MAIN(TestPaintViewWidget)
#include "PaintViewWidgetTest.moc"
