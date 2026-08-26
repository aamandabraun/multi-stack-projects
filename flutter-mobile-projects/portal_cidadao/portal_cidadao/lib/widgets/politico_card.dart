import 'package:flutter/material.dart';

import '../models/politico.dart';
import '../themes/app_theme.dart';

/// Card reutilizável de parlamentar, usado tanto na listagem principal
/// quanto na tela de Favoritos. Centralizar este widget evita
/// duplicação de layout (princípio DRY exigido na especificação).
class PoliticoCard extends StatelessWidget {
  final Politico politico;
  final bool isFavorito;
  final VoidCallback onTap;
  final VoidCallback onToggleFavorito;

  const PoliticoCard({
    super.key,
    required this.politico,
    required this.isFavorito,
    required this.onTap,
    required this.onToggleFavorito,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Card(
      child: InkWell(
        borderRadius: BorderRadius.circular(14),
        onTap: onTap,
        child: Padding(
          padding: const EdgeInsets.all(AppSpacing.md),
          child: Row(
            children: [
              _Avatar(urlFoto: politico.urlFoto, nome: politico.nome),
              const SizedBox(width: AppSpacing.md),
              Expanded(
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      politico.nome,
                      style: theme.textTheme.titleMedium,
                      maxLines: 1,
                      overflow: TextOverflow.ellipsis,
                    ),
                    const SizedBox(height: AppSpacing.xs),
                    Row(
                      children: [
                        Chip(
                          label: Text(politico.siglaPartido),
                          visualDensity: VisualDensity.compact,
                          materialTapTargetSize:
                              MaterialTapTargetSize.shrinkWrap,
                        ),
                        const SizedBox(width: AppSpacing.xs),
                        Chip(
                          label: Text(politico.siglaUf),
                          visualDensity: VisualDensity.compact,
                          materialTapTargetSize:
                              MaterialTapTargetSize.shrinkWrap,
                        ),
                      ],
                    ),
                  ],
                ),
              ),
              IconButton(
                icon: Icon(
                  isFavorito ? Icons.favorite : Icons.favorite_border,
                  color: isFavorito ? AppColors.alerta : null,
                ),
                tooltip: isFavorito
                    ? 'Remover dos favoritos'
                    : 'Salvar para consulta offline',
                onPressed: onToggleFavorito,
              ),
            ],
          ),
        ),
      ),
    );
  }
}

class _Avatar extends StatelessWidget {
  final String urlFoto;
  final String nome;

  const _Avatar({required this.urlFoto, required this.nome});

  @override
  Widget build(BuildContext context) {
    final iniciais = nome.trim().isNotEmpty
        ? nome.trim().substring(0, 1).toUpperCase()
        : '?';

    return CircleAvatar(
      radius: 28,
      backgroundColor:
          Theme.of(context).colorScheme.primaryContainer,
      backgroundImage: urlFoto.isNotEmpty ? NetworkImage(urlFoto) : null,
      onBackgroundImageError: urlFoto.isNotEmpty ? (_, __) {} : null,
      child: urlFoto.isEmpty
          ? Text(
              iniciais,
              style: TextStyle(
                color: Theme.of(context).colorScheme.onPrimaryContainer,
                fontWeight: FontWeight.bold,
              ),
            )
          : null,
    );
  }
}
