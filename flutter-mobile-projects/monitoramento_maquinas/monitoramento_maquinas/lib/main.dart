import 'package:flutter/material.dart';
import 'themes/app_theme.dart';
import 'screens/login_screen.dart';

void main() {
  runApp(const MonitoramentoApp());
}

class MonitoramentoApp extends StatelessWidget {
  const MonitoramentoApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Supervisório de Máquinas',
      debugShowCheckedModeBanner: false,
      // Todo o estilo do app (cores, arredondamentos, tipografia) vem
      // do ThemeData centralizado em app_theme.dart.
      theme: AppTheme.themeData,
      home: const LoginScreen(),
    );
  }
}
