import 'package:flutter/material.dart';

/// Design System centralizado da aplicação.
/// Nenhuma tela deve declarar cores ou raios de borda "soltos":
/// tudo deve vir daqui, seja via [AppTheme.themeData] (ThemeData global)
/// seja via as constantes estáticas abaixo (ex: cores de gravidade).
class AppTheme {
  AppTheme._();

  // Paleta principal
  static const Color background = Color(0xFF0F1420);
  static const Color surface = Color(0xFF1A2233);
  static const Color primary = Color(0xFF00BFA6);
  static const Color textPrimary = Color(0xFFEAF0F7);
  static const Color textSecondary = Color(0xFF8B96A8);

  // Cores semânticas de gravidade/status
  static const Color critico = Color(0xFFE53935);
  static const Color alerta = Color(0xFFFFA726);
  static const Color info = Color(0xFF42A5F5);
  static const Color normal = Color(0xFF66BB6A);

  // Raio de borda padrão do app (usado por cards, botões e inputs)
  static const double radius = 16.0;

  /// Retorna a cor correspondente a uma gravidade/status textual.
  static Color corGravidade(String gravidade) {
    switch (gravidade) {
      case 'Crítico':
      case 'Critico':
        return critico;
      case 'Alerta':
        return alerta;
      case 'Info':
        return info;
      default:
        return normal;
    }
  }

  static ThemeData get themeData {
    return ThemeData(
      useMaterial3: true,
      scaffoldBackgroundColor: background,
      colorScheme: const ColorScheme.dark(
        primary: primary,
        secondary: primary,
        surface: surface,
        error: critico,
      ),
      appBarTheme: const AppBarTheme(
        backgroundColor: background,
        elevation: 0,
        foregroundColor: textPrimary,
        centerTitle: true,
      ),
      cardTheme: CardThemeData(
        color: surface,
        elevation: 0,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(radius),
        ),
        margin: EdgeInsets.zero,
      ),
      elevatedButtonTheme: ElevatedButtonThemeData(
        style: ElevatedButton.styleFrom(
          backgroundColor: primary,
          foregroundColor: Colors.black,
          padding: const EdgeInsets.symmetric(vertical: 16, horizontal: 20),
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(radius),
          ),
          textStyle: const TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
        ),
      ),
      inputDecorationTheme: InputDecorationTheme(
        filled: true,
        fillColor: surface,
        contentPadding: const EdgeInsets.symmetric(vertical: 16, horizontal: 16),
        border: OutlineInputBorder(
          borderRadius: BorderRadius.circular(radius),
          borderSide: BorderSide.none,
        ),
        enabledBorder: OutlineInputBorder(
          borderRadius: BorderRadius.circular(radius),
          borderSide: BorderSide.none,
        ),
        focusedBorder: OutlineInputBorder(
          borderRadius: BorderRadius.circular(radius),
          borderSide: const BorderSide(color: primary, width: 1.5),
        ),
        hintStyle: const TextStyle(color: textSecondary),
      ),
      listTileTheme: ListTileThemeData(
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(radius),
        ),
        tileColor: surface,
      ),
      textTheme: const TextTheme(
        titleLarge: TextStyle(color: textPrimary, fontWeight: FontWeight.bold),
        titleMedium: TextStyle(color: textPrimary, fontWeight: FontWeight.w600),
        bodyMedium: TextStyle(color: textPrimary),
        bodySmall: TextStyle(color: textSecondary),
      ),
      snackBarTheme: SnackBarThemeData(
        backgroundColor: surface,
        contentTextStyle: const TextStyle(color: textPrimary),
        behavior: SnackBarBehavior.floating,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(radius / 2),
        ),
      ),
    );
  }
}
