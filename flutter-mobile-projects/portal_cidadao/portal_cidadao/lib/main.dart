import 'package:flutter/material.dart';

import 'themes/app_theme.dart';
import 'views/politicos_list_screen.dart';

void main() {
  runApp(const PortalCidadaoApp());
}

class PortalCidadaoApp extends StatefulWidget {
  const PortalCidadaoApp({super.key});

  @override
  State<PortalCidadaoApp> createState() => _PortalCidadaoAppState();
}

class _PortalCidadaoAppState extends State<PortalCidadaoApp> {
  // Segue o tema do sistema por padrão; pode ser exposto futuramente
  // como preferência do usuário (ex.: switch em uma tela de ajustes).
  ThemeMode _themeMode = ThemeMode.system;

  void setThemeMode(ThemeMode mode) => setState(() => _themeMode = mode);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Portal Cidadão',
      debugShowCheckedModeBanner: false,
      theme: AppTheme.light,
      darkTheme: AppTheme.dark,
      themeMode: _themeMode,
      home: const PoliticosListScreen(),
    );
  }
}
