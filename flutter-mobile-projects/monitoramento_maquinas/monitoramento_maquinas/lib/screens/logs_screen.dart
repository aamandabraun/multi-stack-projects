import 'package:flutter/material.dart';
import '../models/ocorrencia_model.dart';
import '../themes/app_theme.dart';
import 'filter_screen.dart';

/// Tela 3 - Histórico de Logs de Ocorrência.
///
/// Demonstra:
/// - Ciclo de vida (initState + Future.delayed simulando carregamento).
/// - ListView.builder performático com 50+ itens.
/// - Navegação assíncrona com retorno (await Navigator.push).
/// - Estado local por item via setState (reconhecer/arquivar alarme).
class LogsScreen extends StatefulWidget {
  const LogsScreen({super.key});

  @override
  State<LogsScreen> createState() => _LogsScreenState();
}

class _LogsScreenState extends State<LogsScreen> {
  bool _carregando = true;
  String? _filtroAtual;

  List<OcorrenciaModel> _todasOcorrencias = [];
  List<OcorrenciaModel> _ocorrenciasExibidas = [];

  @override
  void initState() {
    super.initState();
    // Simula uma chamada de rede/banco de dados: enquanto o Future não
    // resolve, o CircularProgressIndicator fica visível na tela.
    Future.delayed(const Duration(seconds: 2), () {
      // Verifica se o widget ainda está montado antes de chamar setState,
      // evitando erro caso o usuário saia da tela durante o delay.
      if (!mounted) return;
      setState(() {
        _todasOcorrencias = _gerarOcorrencias(50);
        _ocorrenciasExibidas = _todasOcorrencias;
        _carregando = false;
      });
    });
  }

  @override
  void dispose() {
    // Nenhum controller de texto é usado nesta tela, mas o método é
    // mantido para liberar quaisquer recursos futuros corretamente.
    super.dispose();
  }

  List<OcorrenciaModel> _gerarOcorrencias(int quantidade) {
    const gravidades = ['Crítico', 'Alerta', 'Info'];
    const titulosBase = [
      'Superaquecimento detectado',
      'Falha de comunicação com sensor',
      'Parada não programada',
      'Nível de óleo abaixo do esperado',
      'Pressão fora da faixa ideal',
      'Manutenção preventiva concluída',
      'Reinicialização do controlador',
      'Vibração acima do limite',
    ];

    return List.generate(quantidade, (index) {
      final gravidade = gravidades[index % gravidades.length];
      return OcorrenciaModel(
        titulo: titulosBase[index % titulosBase.length],
        descricao: 'Máquina ${(index % 12) + 1} • Linha ${String.fromCharCode(65 + (index % 3))}',
        gravidade: gravidade,
        dataHora: DateTime.now().subtract(Duration(minutes: index * 7)),
      );
    });
  }

  Future<void> _abrirFiltro() async {
    // Aguarda o retorno da Tela 4 antes de continuar a execução.
    final filtroSelecionado = await Navigator.push<String>(
      context,
      MaterialPageRoute(builder: (_) => const FilterScreen()),
    );

    if (filtroSelecionado == null || !mounted) return;

    setState(() {
      _filtroAtual = filtroSelecionado;
      _ocorrenciasExibidas = _todasOcorrencias
          .where((ocorrencia) => ocorrencia.gravidade == filtroSelecionado)
          .toList();
    });

    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        content: Text('Exibindo apenas logs do tipo: $filtroSelecionado'),
      ),
    );
  }

  void _limparFiltro() {
    setState(() {
      _filtroAtual = null;
      _ocorrenciasExibidas = _todasOcorrencias;
    });
  }

  void _alternarReconhecimento(OcorrenciaModel ocorrencia) {
    // Altera o estado local daquele item específico e redesenha a tela.
    setState(() {
      ocorrencia.reconhecido = !ocorrencia.reconhecido;
    });
  }

  String _formatarHora(DateTime data) {
    final horas = data.hour.toString().padLeft(2, '0');
    final minutos = data.minute.toString().padLeft(2, '0');
    return '$horas:$minutos';
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Histórico de Ocorrências'),
        actions: [
          IconButton(
            tooltip: 'Filtrar por Gravidade',
            icon: const Icon(Icons.filter_alt_outlined),
            onPressed: _abrirFiltro,
          ),
        ],
      ),
      body: _carregando
          ? const Center(child: CircularProgressIndicator(color: AppTheme.primary))
          : Column(
              children: [
                if (_filtroAtual != null)
                  Container(
                    width: double.infinity,
                    color: AppTheme.surface,
                    padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 10),
                    child: Row(
                      children: [
                        Icon(Icons.filter_alt, size: 18, color: AppTheme.corGravidade(_filtroAtual!)),
                        const SizedBox(width: 8),
                        Expanded(
                          child: Text(
                            'Filtro ativo: $_filtroAtual',
                            style: Theme.of(context).textTheme.bodySmall,
                          ),
                        ),
                        TextButton(
                          onPressed: _limparFiltro,
                          child: const Text('Limpar'),
                        ),
                      ],
                    ),
                  ),
                Expanded(
                  child: ListView.builder(
                    // ListView.builder cria os ListTiles sob demanda,
                    // mantendo a rolagem performática mesmo com 50+ itens.
                    physics: const BouncingScrollPhysics(),
                    padding: const EdgeInsets.symmetric(vertical: 8),
                    itemCount: _ocorrenciasExibidas.length,
                    itemBuilder: (context, index) {
                      final ocorrencia = _ocorrenciasExibidas[index];
                      final cor = AppTheme.corGravidade(ocorrencia.gravidade);

                      return Padding(
                        padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 4),
                        child: Card(
                          child: ListTile(
                            leading: CircleAvatar(
                              backgroundColor: cor.withOpacity(0.15),
                              child: Icon(Icons.bolt, color: cor),
                            ),
                            title: Text(
                              ocorrencia.titulo,
                              style: TextStyle(
                                decoration: ocorrencia.reconhecido
                                    ? TextDecoration.lineThrough
                                    : TextDecoration.none,
                                color: ocorrencia.reconhecido
                                    ? AppTheme.textSecondary
                                    : AppTheme.textPrimary,
                                fontWeight: FontWeight.w600,
                              ),
                            ),
                            subtitle: Text(
                              '${ocorrencia.descricao} • ${_formatarHora(ocorrencia.dataHora)} • ${ocorrencia.gravidade}',
                              style: Theme.of(context).textTheme.bodySmall,
                            ),
                            trailing: IconButton(
                              tooltip: ocorrencia.reconhecido
                                  ? 'Reabrir alarme'
                                  : 'Reconhecer alarme',
                              icon: Icon(
                                ocorrencia.reconhecido
                                    ? Icons.check_circle
                                    : Icons.check_circle_outline,
                                color: ocorrencia.reconhecido ? AppTheme.normal : AppTheme.textSecondary,
                              ),
                              onPressed: () => _alternarReconhecimento(ocorrencia),
                            ),
                          ),
                        ),
                      );
                    },
                  ),
                ),
              ],
            ),
    );
  }
}
