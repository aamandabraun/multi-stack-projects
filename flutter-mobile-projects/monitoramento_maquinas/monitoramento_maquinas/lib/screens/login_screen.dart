import 'package:flutter/material.dart';
import '../themes/app_theme.dart';
import '../widgets/custom_action_button.dart';
import 'dashboard_screen.dart';

/// Tela 1 - Portal de Acesso.
/// Demonstra uso de TextEditingController + dispose() para liberar
/// recursos corretamente quando a tela sai da árvore de widgets.
class LoginScreen extends StatefulWidget {
  const LoginScreen({super.key});

  @override
  State<LoginScreen> createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final TextEditingController _usuarioController = TextEditingController();
  final TextEditingController _senhaController = TextEditingController();

  @override
  void dispose() {
    // Libera os controllers para evitar vazamento de memória.
    _usuarioController.dispose();
    _senhaController.dispose();
    super.dispose();
  }

  void _entrar() {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (_) => const DashboardScreen()),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Center(
          child: SingleChildScrollView(
            padding: const EdgeInsets.symmetric(horizontal: 28),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                const Icon(Icons.precision_manufacturing,
                    size: 72, color: AppTheme.primary),
                const SizedBox(height: 16),
                Text(
                  'Supervisório de Máquinas',
                  textAlign: TextAlign.center,
                  style: Theme.of(context).textTheme.titleLarge?.copyWith(
                        fontSize: 24,
                      ),
                ),
                const SizedBox(height: 4),
                Text(
                  'Acesse com suas credenciais de operador',
                  textAlign: TextAlign.center,
                  style: Theme.of(context).textTheme.bodySmall,
                ),
                const SizedBox(height: 32),
                TextField(
                  controller: _usuarioController,
                  style: const TextStyle(color: AppTheme.textPrimary),
                  decoration: const InputDecoration(
                    hintText: 'Usuário',
                    prefixIcon: Icon(Icons.person_outline),
                  ),
                ),
                const SizedBox(height: 16),
                TextField(
                  controller: _senhaController,
                  obscureText: true,
                  style: const TextStyle(color: AppTheme.textPrimary),
                  decoration: const InputDecoration(
                    hintText: 'Senha',
                    prefixIcon: Icon(Icons.lock_outline),
                  ),
                ),
                const SizedBox(height: 24),
                CustomActionButton(
                  label: 'Entrar',
                  icon: Icons.login,
                  onPressed: _entrar,
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
