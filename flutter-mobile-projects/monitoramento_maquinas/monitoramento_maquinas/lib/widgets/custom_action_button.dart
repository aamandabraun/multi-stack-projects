import 'package:flutter/material.dart';
import '../themes/app_theme.dart';

/// Botão de ação reutilizável, usado em todo o app sempre que
/// precisamos de um botão com ícone + rótulo + callback.
/// Evita repetir estilo de botão em cada tela (DRY).
class CustomActionButton extends StatelessWidget {
  final String label;
  final IconData icon;
  final VoidCallback onPressed;
  final Color? color;
  final bool expandido;

  const CustomActionButton({
    super.key,
    required this.label,
    required this.icon,
    required this.onPressed,
    this.color,
    this.expandido = true,
  });

  @override
  Widget build(BuildContext context) {
    final botao = ElevatedButton.icon(
      onPressed: onPressed,
      icon: Icon(icon),
      label: Text(label),
      style: color != null
          ? ElevatedButton.styleFrom(
              backgroundColor: color,
              foregroundColor: Colors.white,
              padding: const EdgeInsets.symmetric(vertical: 16, horizontal: 20),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(AppTheme.radius),
              ),
            )
          : null,
    );

    return expandido ? SizedBox(width: double.infinity, child: botao) : botao;
  }
}
