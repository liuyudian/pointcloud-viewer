#ifndef POINTCLOUDVIEWER_USABILILTY_SCHEME_HPP_
#define POINTCLOUDVIEWER_USABILILTY_SCHEME_HPP_

#include <QMouseEvent>
#include <QSharedPointer>
#include <QVector>

#include <pointcloud_viewer/navigation.hpp>

// Different Usability schemes on how to navigate the 3d space

class UsabilityScheme final : public QObject
{
  Q_OBJECT
public:
  enum scheme_t
  {
    BLENDER = 0,
    MESHLAB = 1,
  };

  UsabilityScheme(Navigation::Controller& navigation);
  ~UsabilityScheme();

  void enableBlenderScheme();
  void enableMeshlabScheme();

  void enableScheme(scheme_t scheme);
  scheme_t enabled_scheme() const;

  void wheelEvent(QWheelEvent* event);
  void mouseMoveEvent(glm::vec2 mouse_force, QMouseEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent* event);
  void fps_mode_changed(bool enabled_fps_mode);

  QKeySequence fps_activation_key_sequence();

  static QString scheme_as_string(scheme_t scheme);
  static scheme_t scheme_from_string(QString scheme);

signals:
  void fpsActivationKeySequenceChanged(QKeySequence keySequence);

private:
  class Implementation;

  Implementation* _implementation = nullptr;

  QMap<scheme_t, QSharedPointer<Implementation>> implementations;
};

class UsabilityScheme::Implementation
{
public:
  class BlenderScheme;
  class MeshLabScheme;

  Navigation::Controller& navigation;

  Implementation(Navigation::Controller& navigation);
  virtual ~Implementation() = default;

  virtual void on_enable() = 0;
  virtual void on_disable() = 0;

  virtual void wheelEvent(QWheelEvent* event) = 0;
  virtual void mouseMoveEvent(glm::vec2 mouse_force, QMouseEvent* event) = 0;
  virtual void mousePressEvent(QMouseEvent* event) = 0;
  virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
  virtual void keyPressEvent(QKeyEvent* event) = 0;
  virtual void keyReleaseEvent(QKeyEvent* event) = 0;
  virtual void fps_mode_changed(bool enabled_fps_mode) = 0;
  virtual QKeySequence fps_activation_key_sequence() = 0;
};
#endif // POINTCLOUDVIEWER_USABILILTY_SCHEME_HPP_
