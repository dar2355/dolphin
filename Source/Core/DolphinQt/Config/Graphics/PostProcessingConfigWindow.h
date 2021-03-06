// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <QDialog>

#include "Common/CommonTypes.h"
#include "VideoCommon/PostProcessing.h"

class EnhancementsWidget;
class QCheckBox;
class QDialogButtonBox;
class QGridLayout;
class QLineEdit;
class QSlider;
class QTabWidget;
class QWidget;

class PostProcessingConfigWindow final : public QDialog
{
  Q_OBJECT
public:
  explicit PostProcessingConfigWindow(EnhancementsWidget* parent, const std::string& shader);
  ~PostProcessingConfigWindow();

private:
  class ConfigGroup final
  {
  public:
    explicit ConfigGroup(
        const PostProcessingShaderConfiguration::ConfigurationOption* config_option);

    const std::string& GetGUIName() const noexcept;
    const std::string& GetParent() const noexcept;
    const std::string& GetOptionName() const noexcept;
    void AddSubGroup(std::unique_ptr<ConfigGroup>&& subgroup);
    bool HasSubGroups() const noexcept;
    const std::vector<std::unique_ptr<ConfigGroup>>& GetSubGroups() const noexcept;
    u32 AddWidgets(PostProcessingConfigWindow* parent, QGridLayout* grid, u32 row);
    void EnableSuboptions(bool state);
    int GetSliderValue(size_t index) const;
    void SetSliderText(size_t index, const QString& text);

  private:
    u32 AddBool(PostProcessingConfigWindow* parent, QGridLayout* grid, u32 row);
    u32 AddInteger(PostProcessingConfigWindow* parent, QGridLayout* grid, u32 row);
    u32 AddFloat(PostProcessingConfigWindow* parent, QGridLayout* grid, u32 row);

    QCheckBox* m_checkbox;
    std::vector<QSlider*> m_sliders;
    std::vector<QLineEdit*> m_value_boxes;

    const PostProcessingShaderConfiguration::ConfigurationOption* m_config_option;
    std::vector<std::unique_ptr<ConfigGroup>> m_subgroups;
  };
  void Create();
  void ConnectWidgets();
  QWidget* CreateDependentTab(const std::unique_ptr<ConfigGroup>& config_group);
  void PopulateGroups();
  void UpdateBool(ConfigGroup* config_group, bool state);
  void UpdateInteger(ConfigGroup* config_group, int value);
  void UpdateFloat(ConfigGroup* config_group, int value);

  QTabWidget* m_tabs;
  QDialogButtonBox* m_buttons;

  const std::string& m_shader;
  PostProcessingShaderConfiguration* m_post_processor;
  std::unordered_map<std::string, ConfigGroup*> m_config_map;
  std::vector<std::unique_ptr<ConfigGroup>> m_config_groups;
};
