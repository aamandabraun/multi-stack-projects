import 'package:flutter/material.dart';
import '../models/sensor_model.dart';
import '../themes/app_theme.dart';

/// Card reutilizável para exibir um indicador/sensor no GridView do
/// Dashboard. Concentra toda a formatação visual do card em um único
/// lugar (DRY + design system centralizado).
class IndicatorCard extends StatelessWidget {
  final SensorModel sensor;
  final VoidCallback? onTap;

  const IndicatorCard({super.key, required this.sensor, this.onTap});

  @override
  Widget build(BuildContext context) {
    final corStatus = AppTheme.corGravidade(
      sensor.status == 'Critico' ? 'Crítico' : sensor.status,
    );

    return Card(
      child: InkWell(
        borderRadius: BorderRadius.circular(AppTheme.radius),
        onTap: onTap,
        child: Padding(
          padding: const EdgeInsets.all(16),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Icon(sensor.icone, color: AppTheme.primary, size: 28),
                  Container(
                    width: 10,
                    height: 10,
                    decoration: BoxDecoration(
                      color: corStatus,
                      shape: BoxShape.circle,
                    ),
                  ),
                ],
              ),
              const Spacer(),
              Text(
                sensor.nome,
                style: Theme.of(context).textTheme.titleMedium,
                maxLines: 1,
                overflow: TextOverflow.ellipsis,
              ),
              const SizedBox(height: 4),
              Text(
                sensor.localizacao,
                style: Theme.of(context).textTheme.bodySmall,
              ),
              const SizedBox(height: 8),
              Text(
                '${sensor.valor.toStringAsFixed(1)} ${sensor.unidade}',
                style: const TextStyle(
                  color: AppTheme.textPrimary,
                  fontSize: 20,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
