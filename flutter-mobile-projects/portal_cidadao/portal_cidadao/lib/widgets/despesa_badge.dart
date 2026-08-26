import 'package:flutter/material.dart';

import '../models/despesa.dart';
import '../themes/app_theme.dart';

/// Badge de status de uma despesa: verde quando o valor líquido
/// reembolsado é integral, laranja quando houve glosa (parte do valor
/// não foi ressarcida). Reutilizado em qualquer lista de despesas.
class DespesaBadge extends StatelessWidget {
  final Despesa despesa;

  const DespesaBadge({super.key, required this.despesa});

  @override
  Widget build(BuildContext context) {
    final houveGlosa = despesa.valorGlosa > 0;

    final cor = houveGlosa ? AppColors.alerta : AppColors.secondary;
    final texto = houveGlosa ? 'Com glosa' : 'Reembolso integral';
    final icone = houveGlosa ? Icons.report_gmailerrorred : Icons.check_circle;

    return Container(
      padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 3),
      decoration: BoxDecoration(
        color: cor.withOpacity(0.12),
        borderRadius: BorderRadius.circular(20),
      ),
      child: Row(
        mainAxisSize: MainAxisSize.min,
        children: [
          Icon(icone, size: 14, color: cor),
          const SizedBox(width: 4),
          Text(
            texto,
            style: TextStyle(
              color: cor,
              fontSize: 11,
              fontWeight: FontWeight.w600,
            ),
          ),
        ],
      ),
    );
  }
}
