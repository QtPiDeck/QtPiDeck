#pragma once

#include <memory>

#include <QSettings>

#include "Services/IClientSettingsStorage.hpp"

namespace QtPiDeck::Services {
class SettingsStorage final : public IClientSettingsStorage {
public:
    SettingsStorage();
    SettingsStorage(const SettingsStorage&) = delete;
    SettingsStorage(SettingsStorage&&) = default;
    ~SettingsStorage() final = default;

    auto operator=(const SettingsStorage&) -> SettingsStorage& = delete;
    auto operator=(SettingsStorage&&) -> SettingsStorage& = default;

    [[nodiscard]] auto read(const QString& key, const QVariant& defaultValue = QVariant{}) const noexcept -> QVariant final;
    void store(const QString& key, const QVariant& value) noexcept final;

    [[nodiscard]] auto deckServerAddress() const noexcept -> QString final;
    void setDeckServerAddress(const QString& deckServerAddress) noexcept final;
    [[nodiscard]] auto deckServerPort() const noexcept -> QString final;
    void setDeckServerPort(const QString& deckServerPort) noexcept final;
private:
    std::unique_ptr<QSettings> m_settings;

    inline static const QString DeckServerAddressKey{"DeckServerAddress"};
    inline static const QString DeckServerAddressDefaultValue{"127.0.0.1"};
    inline static const QString DeckServerPortKey{"DeckServerPort"};
    inline static const QString DeckServerPortDefaultValue{"13000"};
};
}
